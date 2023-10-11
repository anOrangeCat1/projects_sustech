import pandas as pd
import numpy as np
import torch
from d2l import torch as d2l
from torch import nn
import matplotlib.pyplot as plt


import hashlib
import os
import tarfile
import zipfile
import requests


DATA_HUB = dict()
DATA_URL = 'http://d2l-data.s3-accelerate.amazonaws.com/'


# 下⾯的download函数⽤来下载数据集，将数据集缓存在本地⽬录（默认情况下为../data）中，
# 并返回下载⽂件的名称。如果缓存⽬录中已经存在此数据集⽂件，
# 并且其sha-1与存储在DATA_HUB中的相匹配，我们将使⽤缓存的⽂件，以避免重复的下载。
def download(name, cache_dir=os.path.join('..', 'data')):
    """下载一个DATA_HUB中的文件, 返回本地文件名"""
    assert name in DATA_HUB, f"{name} 不存在于 {DATA_HUB}"
    url, sha1_hash = DATA_HUB[name]
    fname = os.path.join(cache_dir, url.split('/')[-1])
    if os.path.exists(fname):
        sha1 = hashlib.sha1()
        with open(fname, 'rb')as f:
            while True:
                data = f.read(1048576)
                if not data:
                    break
                sha1.update(data)
        if sha1.hexdigest() == sha1_hash:
            return fname  # 命中缓存
    print(f'正在从{url}下载{fname}...')
    r = requests.get(url, stream=True, verify=True)
    with open(fname, 'wb') as f:
        f.write(r.content)
    return fname


# 我们还需实现两个实⽤函数：⼀个将下载并解压缩⼀个zip或tar⽂件，
# 另⼀个是将本书中使⽤的所有数据集从DATA_HUB下载到缓存⽬录中。
def download_extract(name, folder=None):  # @save
    """下载并解压zip/tar⽂件"""
    fname = download(name)
    base_dir = os.path.dirname(fname)
    data_dir, ext = os.path.splitext(fname)
    if ext == '.zip':
        fp = zipfile.ZipFile(fname, 'r')
    elif ext in ('.tar', '.gz'):
        fp = tarfile.open(fname, 'r')
    else:
        assert False, '只有zip/tar⽂件可以被解压缩'
    fp.extractall(base_dir)
    return os.path.join(base_dir, folder) if folder else data_dir


def download_all():  # @save
    """下载DATA_HUB中的所有⽂件"""
    for name in DATA_HUB:
        download(name)


# 开始之前，我们将使⽤pandas读⼊并处理数据
DATA_HUB['kaggle_house_train'] = (  # @save
    DATA_URL + 'kaggle_house_pred_train.csv',
    '585e9cc93e70b39160e7921475f9bcd7d31219ce')
DATA_HUB['kaggle_house_test'] = (  # @save
    DATA_URL + 'kaggle_house_pred_test.csv',
    'fa19780a7b011d9b009e8bff8e99922a8ee2eb90')

train_data = pd.read_csv(download('kaggle_house_train'))
test_data = pd.read_csv(download('kaggle_house_test'))

# print(train_data.shape)
# print(type(train_data))
# print(test_data.shape)
# 第⼀个特征是ID
# 虽然这很⽅便，但它不携带任何⽤于预测的信息。
# 因此，在将数据提供给模型之前，我们将其从数据集中删除。
all_features = pd.concat((train_data.iloc[:, 1:-1], test_data.iloc[:, 1:]))


# 数据预处理
# ⾸先，我们将所有缺失的值替换为相应特征的平均值。
# 然后，为了将所有特征放在⼀个共同的尺度上，
# 我们通过将特征重新缩放到零均值和单位⽅差来标准化数据：
# x <- (x-u)/s  u = 均值  s = 标准差
# 若⽆法获得测试数据，则可根据训练数据计算均值和标准差
numeric_features = all_features.dtypes[all_features.dtypes != 'object'].index
all_features[numeric_features] = all_features[numeric_features].apply(
    lambda x: (x - x.mean()) / (x.std()))
# 在标准化数据之后，所有均值消失，因此我们可以将缺失值设置为0
all_features[numeric_features] = all_features[numeric_features].fillna(0)


# “Dummy_na=True”将“na”（缺失值）视为有效的特征值，并为其创建指⽰符特征
all_features = pd.get_dummies(all_features, dummy_na=True)

print(all_features.shape)

# 此转换会将特征的总数量从79个增加到331个。
# 最后，通过values属性，我们可以从pandas格式中提取NumPy格式，
# 并将其转换为张量表⽰⽤于训练。
n_train = train_data.shape[0]
train_features = torch.tensor(
    all_features[:n_train].values, dtype=torch.float32)
test_features = torch.tensor(
    all_features[n_train:].values, dtype=torch.float32)
train_labels = torch.tensor(
    train_data.SalePrice.values.reshape(-1, 1), dtype=torch.float32)

print(n_train)
print(train_features.shape,train_labels.shape)

# 训练
loss = nn.MSELoss()
in_features = train_features.shape[1]  # feature个数


def get_net():
    net = nn.Sequential(nn.Linear(in_features, 1))
    return net


def log_rmse(net, features, labels):
    # 为了在取对数时进⼀步稳定该值，将⼩于1的值设置为1
    clipped_preds = torch.clamp(net(features), 1, float('inf'))
    rmse = torch.sqrt(loss(torch.log(clipped_preds), torch.log(labels)))
    return rmse


# 训练函数将借助Adam优化器（我们将在后⾯章节更详细地描述它)
# Adam优化器的主要吸引⼒在于它对初始学习率不那么敏感。
def train(net, train_features, train_labels,
          test_features, test_labels, num_epochs,
          learning_rate, weight_decay, batch_size):
    train_ls, test_ls = [], []
    train_iter = d2l.load_array((train_features, train_labels), batch_size)
    # 这⾥使⽤的是Adam优化算法
    optimizer = torch.optim.Adam(net.parameters(),
                                 lr=learning_rate,
                                 weight_decay=weight_decay)
    for epoch in range(num_epochs):
        for X, y in train_iter:
            optimizer.zero_grad()
            l = loss(net(X), y)
            l.backward()
            optimizer.step()
        train_ls.append(log_rmse(net, train_features, train_labels))
        if test_labels is not None:
            test_ls.append(log_rmse(net, test_features, test_labels))
    return train_ls, test_ls


# K折交叉验证
# 它选择第i个切⽚作为验证数据，其余部分作为训练数据
def get_k_fold_data(k, i, X, y):
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


# 当我们在K折交叉验证中训练K次后，返回训练和验证误差的平均值
def k_fold(k, X_train, y_train, num_epochs,
           learning_rate, weight_decay, batch_size):
    train_l_sum, valid_l_sum = 0, 0
    for i in range(k):
        data = get_k_fold_data(k, i, X_train, y_train)
        net = get_net()
        train_ls, valid_ls = train(net, *data, num_epochs, learning_rate,
                                   weight_decay, batch_size)
        train_l_sum += train_ls[-1]
        valid_l_sum += valid_ls[-1]
        # print(type(train_ls))
        if i == 0:
            pass
            plt.plot(list(range(1, num_epochs + 1)), torch.tensor(train_ls),
                     list(range(1, num_epochs + 1)), torch.tensor(valid_ls))
            plt.show()
            d2l.plot(list(range(1, num_epochs + 1)), [torch.tensor(train_ls), torch.tensor(valid_ls)],
                     xlabel='epoch', ylabel='rmse', xlim=[1, num_epochs],
                     legend=['train', 'valid'], yscale='log')
        print(f'折{i + 1}，训练log rmse{float(train_ls[-1]):f}, '
              f'验证log rmse{float(valid_ls[-1]):f}')
    return train_l_sum/k, valid_l_sum/k


# 模型选择
k, num_epochs, lr, weight_decay, batch_size = 5, 100, 5, 0, 64
train_l, valid_l = k_fold(k, train_features, train_labels,
                          num_epochs, lr, weight_decay, batch_size)

print(f'{k}-折验证: 平均训练log rmse: {float(train_l):f}, '
      f'平均验证log rmse: {float(valid_l):f}')
