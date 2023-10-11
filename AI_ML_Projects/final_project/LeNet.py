import torch
import torch.nn as nn
import numpy as np
import pandas as pd
from torch.utils import data
import matplotlib.pyplot as plt
from sklearn.metrics import f1_score


# 首先进行数据处理
# 从csv文件中读取数据
csv_data = pd.read_csv("./ecg_data.csv")
# 转化为张量torch.tensor, 用于后续训练
all_data = torch.tensor(csv_data.values, dtype=torch.float32)
# print(all_data.shape)  --> [8527, 189]
# 8527个样本    188个features   最后1列为类别: 1, 2, 3, 4
# all_features取[:,188]   all_labels取[:,-1]
n_data = all_data.shape[0]  # 样本数, 即为行数(dim = 0)
n_features = all_data.shape[1]-1  # features个数, 最后一列为label
n_test = n_data//5  # //表示取整除 如7//2=3
n_train = n_data-n_test
# print(n_data, n_features, n_train, n_test)
all_features = all_data[:, :n_features]
all_labels = all_data[:, -1:]


def make_iter(features, labels, batch_s):
    """使用features和labels构建相应的迭代器"""
    # 用TensorDataset捆绑features和labels
    data_set = data.TensorDataset(features, labels)
    # 定义数据加载器
    data_loader = data.DataLoader(dataset=data_set,
                                  batch_size=batch_s,
                                  shuffle=True)

    return data_loader


class LeNet(nn.Module):
    """LeNet
    使用CNN一定要注意输入input的张量维数
    其具体结构如下
    """

    def __init__(self):
        super().__init__()
        self.net = nn.Sequential(
            nn.Conv1d(1, 2, kernel_size=5, padding=2), nn.ReLU(),
            nn.AvgPool1d(kernel_size=2, stride=2),
            nn.Conv1d(2, 4, kernel_size=5), nn.ReLU(),
            nn.AvgPool1d(kernel_size=2, stride=2),
            nn.Flatten(),
            nn.Linear(180, 84), nn.ReLU(),
            nn.Linear(84, 32), nn.ReLU(),
            nn.Linear(32, 4)
        )

    def forward(self, x):
        output = self.net(x)

        return output


# 定义使用的模型和损失函数
# 因为这是一个4分类问题, 故使用交叉熵作为损失函数计算loss
my_net = LeNet()
loss = nn.CrossEntropyLoss()


def calculate_param(net, features, labels):
    """使用交叉熵计算loss
    此处batch_size等于整个数据集大小, 即一次性把所有数据作为输入进行计算
    封装成函数的原因是可以方便计算 loss, Fnorm, Faf, Foth 以及 Ft(final accuracy)
    根据文档可知: Ft = ( Fnorm + Faf + Foth )/3
    同时也可以很方便地计算 训练集(train) 的参数和 测试集(test) 的参数
    注意CNN的输入张量维数与MLP不同
    """

    iter = make_iter(features, labels, labels.size()[0])
    for A, b in iter:
        # 对维数进行处理
        A1 = A.unsqueeze(1)
        b_hat = net(A1)
        b = b-torch.ones(b.size())
        b = b.squeeze()
        ls = loss(b_hat, b.to(torch.long))
        # TP = torch.sum(b.flatten() == torch.argmax(b_hat, dim=1))
        pred = torch.argmax(b_hat, dim=1)
        test = b.flatten()
        # 注意此处average='micro' 与 'macro' 有区别
        score = np.array([f1_score(pred, test, labels=[0], average='micro'),
                          f1_score(pred, test, labels=[1], average='micro'),
                          f1_score(pred, test, labels=[2], average='micro'), ])
        fn = score[0]
        fa = score[1]
        fo = score[2]
        f = score.sum()*1.0 / len(score)
        # f = f1_score(pred, test, average='macro')

    # acc = TP.data.numpy() / len(features)

    return ls, fn, fa, fo, f


def train(net, loss, train_features, train_labels,
          test_features, test_labels, num_epochs,
          learning_rate, weight_decay, batch_size):
    train_ls, train_fn, train_fa, train_fo, train_f = [], [], [], [], []
    test_ls, test_fn, test_fa, test_fo, test_f = [], [], [], [], []
    # 生成训练数据集和验证数据集的迭代器
    train_iter = make_iter(train_features, train_labels, batch_size)
    # test_iter = make_iter(test_features, test_labels, 1705)
    # 这⾥使⽤的是Adam优化算法
    # 此处经过测试Adam优化算法比SDG优化算法效果好了非常多
    # Adam优势在于对于初始的学习率并不敏感
    optimizer = torch.optim.Adam(net.parameters(),
                                 lr=learning_rate,
                                 weight_decay=weight_decay)
    for epoch in range(num_epochs):
        for X, y in train_iter:
            # 此处一定注意！！
            # 卷积神经网络CNN输入张量的维数与MLP不同
            X1 = X.unsqueeze(1)
            optimizer.zero_grad()  # 将梯度清零
            y_hat = net(X1)  # 将数据输入网络
            # 处理y, 使之可以使用交叉熵计算loss
            y = y-torch.ones(y.size())
            y = y.squeeze()
            # print(y_hat.size(), y.size())
            ls = loss(y_hat, y.to(torch.long))  # 计算loss值

            ls.backward()  # 误差反向传播
            optimizer.step()  # 参数更新
            # running_loss += ls.item()  # 将每轮的loss求和
        tr_ls, tr_fn, tr_fa, tr_fo, tr_f = calculate_param(
            net, train_features, train_labels)
        train_ls.append(tr_ls)
        train_fn.append(tr_fn)
        train_fa.append(tr_fa)
        train_fo.append(tr_fo)
        train_f.append(tr_f)
        if test_labels is not None:
            te_ls, te_fn, te_fa, te_fo, te_f = calculate_param(
                net, test_features, test_labels)
            test_ls.append(te_ls)
            test_fn.append(te_fn)
            test_fa.append(te_fa)
            test_fo.append(te_fo)
            test_f.append(te_f)
        # print(f'train_tp: {tr_acc:f}',
        #       f'test_tp {te_acc:f}')

    return train_ls, test_ls, train_f, test_fn, test_fa, test_fo, test_f


def get_k_fold_data(k, i, X, y):
    """K折交叉验证
    它选择第i个切⽚作为验证数据，其余部分作为训练数据
    """
    assert k > 1
    fold_size = X.shape[0]//k  # //表示取整除 如7//2=3
    X_train, y_train = None, None
    for j in range(k):
        idx = slice(j*fold_size, (j+1)*fold_size)
        X_part, y_part = X[idx, :], y[idx]
        if j == i:
            X_valid, y_valid = X_part, y_part
        elif X_train is None:
            X_train, y_train = X_part, y_part
        else:
            X_train = torch.cat([X_train, X_part], 0)
            y_train = torch.cat([y_train, y_part], 0)
    return X_train, y_train, X_valid, y_valid


def k_fold(k, my_net, loss, all_features, all_labels, num_epochs,
           learning_rate, weight_decay, batch_size):
    """当我们在K折交叉验证中训练K次后，返回训练和验证误差的平均值"""
    train_l_sum, valid_l_sum, train_f_sum, valid_f_sum, fn_sum, fa_sum, fo_sum = 0, 0, 0, 0, 0, 0, 0
    for i in range(k):
        data = get_k_fold_data(k, i, all_features, all_labels)
        net = my_net
        train_ls, valid_ls, train_f, valid_fn, valid_fa, valid_fo, valid_f = train(net, loss, *data, num_epochs, learning_rate,
                                                                                   weight_decay, batch_size)
        train_l_sum += train_ls[-1]
        valid_l_sum += valid_ls[-1]
        train_f_sum += train_f[-1]
        valid_f_sum += valid_f[-1]
        fn_sum += valid_fn[-1]
        fa_sum += valid_fa[-1]
        fo_sum += valid_fo[-1]
        # print(type(train_ls))
        if i == 0:
            axis = list(range(1, num_epochs + 1))
            # 最开始(第1折)图像最明显
            plt.figure(1)
            plt.plot(axis, torch.tensor(train_ls),
                     color="b", label="Train Loss")
            plt.plot(axis, torch.tensor(valid_ls),
                     color="r", label="Test Loss")
            plt.xlabel("Epoch(times)")
            plt.ylabel("Loss")
            plt.title("Loss Figure of LeNet")
            plt.legend()
            plt.show()

            plt.figure(2)
            plt.plot(axis, torch.tensor(valid_f), color="g",
                     label="Ft Score")
            plt.xlabel("Epoch(times)")
            plt.ylabel("Final Accuracy Ft")
            plt.legend()
            plt.show()
            # plt.plot(list(range(1, num_epochs + 1)), torch.tensor(train_ls),
            #          list(range(1, num_epochs + 1)), torch.tensor(valid_ls))
            # plt.show()

        print("-"*40)
        print(f'折{i + 1}，训练loss{float(train_ls[-1]):f}, '
              f'验证loss{float(valid_ls[-1]):f}')
        print(f'train_f: {float(train_f[-1]):f}, '
              f'test_f: {float(valid_f[-1]):f}')
        print(f'fn: {float(valid_fn[-1]):f}, '
              f'fa: {float(valid_fa[-1]):f}, '
              f'fo: {float(valid_fo[-1]):f}')
    return train_l_sum/k, valid_l_sum/k, train_f_sum/k, valid_f_sum/k


# 参数选择
# k=5 文档建议为5折 此处采用5折交叉验证 并训练5次取平均
# 经过尝试 学习率lr=0.0005时效果不错
k, num_epochs, lr, weight_decay, batch_size = 5, 100, 0.0005, 0, all_features.shape[0]//5
train_l, valid_l, train_f, valid_f = k_fold(k, my_net, loss, all_features, all_labels,
                                            num_epochs, lr, weight_decay, batch_size)
print("-"*40)
print(f'{k}-折验证: 平均训练loss: {float(train_l):f}, '
      f'平均验证loss: {float(valid_l):f} ')
print(f'平均训练f: {float(train_f):f}, '
      f'平均验证f: {float(valid_f):f}')
print(f'lr= {lr}')
