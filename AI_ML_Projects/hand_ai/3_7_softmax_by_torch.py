import torch
from torch import nn
from d2l import torch as d2l


# 本次使用数据集为 Fashion-MNIST数据集
batch_size = 256
train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size)


# softmax回归的输出层是一个全连接层
# PyTorch不会隐式地调整输入的形状。因此，
# 我们在线性层前定义了展平层(flatten)，来调整网络输入的形状
net = nn.Sequential(nn.Flatten(), nn.Linear(784, 10))


def init_weights(m):
    """初始化模型参数
    均值0 标准差0.01 随机初始化权重
    """
    if type(m) == nn.Linear:
        nn.init.normal_(m.weight, std=0.01)


net.apply(init_weights)


# 我们没有将softmax概率传递到损失函数中，
# ⽽是在交叉熵损失函数中传递未规范化的预测，
# 并同时计算softmax及其对数，
# 这是⼀种类似”LogSumExp技巧”的聪明⽅式。
loss = nn.CrossEntropyLoss(reduction='none')

# 优化算法
# 在这⾥，我们使⽤学习率为0.1的⼩批量随机梯度下降作为优化算法。
# 这与我们在线性回归例⼦中的相同，这说明了优化器的普适性。
trainer = torch.optim.SGD(net.parameters(), lr=0.1)


# 训练
# 调⽤3.6节中定义的训练函数来训练模型
num_epochs = 10
d2l.train_ch3(net, train_iter, test_iter, loss, num_epochs, trainer)


def predict_ch3(net, test_iter, n=6):  # @save
    """预测标签(定义⻅第3章)"""
    for X, y in test_iter:
        break
    trues = d2l.get_fashion_mnist_labels(y)
    preds = d2l.get_fashion_mnist_labels(net(X).argmax(axis=1))
    titles = [true + '\n' + pred for true, pred in zip(trues, preds)]
    d2l.show_images(
        X[0:n].reshape((n, 28, 28)), 1, n, titles=titles[0:n])


predict_ch3(net, test_iter)
