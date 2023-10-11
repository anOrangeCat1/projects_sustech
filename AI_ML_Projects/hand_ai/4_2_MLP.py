import torch
from torch import nn
from d2l import torch as d2l

# 使⽤Fashion-MNIST图像分类数据集
batch_size = 256
train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size)

# 实现一个具有单隐藏层的多层感知机
# 它包含256个隐藏单元
# Fashion-MNIST中的每个图像由28 x 28 = 784个灰度像素值组成
# 所有图像共分为10个类别
# 我们可以将每个图像视为具有784个输⼊特征和10个类的简单分类数据集
num_inputs, num_outputs, num_hiddens = 784, 10, 256

# 初始化模型参数
# randn() 正态分布    rand() 均匀分布
# 注意nn.Parameter()中P要大写
W1 = nn.Parameter(torch.randn(
    num_inputs, num_hiddens, requires_grad=True)*0.01)
b1 = nn.Parameter(torch.zeros(num_hiddens, requires_grad=True))
W2 = nn.Parameter(torch.randn(
    num_hiddens, num_outputs, requires_grad=True)*0.01)
b2 = nn.Parameter(torch.zeros(num_outputs, requires_grad=True))

params = [W1, b1, W2, b2]


# 激活函数
def relu(X):
    a = torch.zeros_like(X)
    return torch.max(X, a)


# 模型
def net(X):
    # 使⽤reshape将每个⼆维图像转换为⼀个⻓度为num_inputs的向量
    # reshape
    X = X.reshape((-1, num_inputs))
    # "@" 代表矩阵乘法
    H = relu(X@W1+b1)
    return (H@W2+b2)


# 损失函数
# reduction='none': 每个step的损失都单独保留
loss = nn.CrossEntropyLoss(reduction='none')


# 训练
num_epochs, lr = 10, 0.1
updater = torch.optim.SGD(params, lr=lr)
d2l.train_ch3(net, train_iter, test_iter, loss, num_epochs, updater)

d2l.predict_ch3(net, test_iter)
