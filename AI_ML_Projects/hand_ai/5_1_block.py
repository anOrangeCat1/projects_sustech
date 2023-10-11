import torch
from torch import nn
from torch.nn import functional as F

"""
简要总结⼀下每个块必须提供的基本功能：
1. 将输⼊数据作为其前向传播函数的参数。
2. 通过前向传播函数来⽣成输出。请注意，输出的形状可能与输⼊的形状不同。
例如, 我们上⾯模型中的第⼀个全连接的层,
接收⼀个20维的输⼊,但是返回⼀个维度为256的输出。
3. 计算其输出关于输⼊的梯度，可通过其反向传播函数进⾏访问。通常这是⾃动发⽣的。
4. 存储和访问前向传播计算所需的参数。
5. 根据需要初始化模型参数。
"""


X = torch.rand(2, 20)


class MLP(nn.Module):
    # 用模型参数声明层。这里，我们声明两个全连接的层
    def __init__(self):
        # 调⽤MLP的⽗类Module的构造函数来执⾏必要的初始化。
        # 这样，在类实例化时也可以指定其他函数参数，例如模型参数params
        super().__init__()
        self.hidden = nn.Linear(20, 256)  # 隐藏层
        self.out = nn.Linear(256, 10)  # 输出层

    # 定义模型的前向传播，即如何根据输⼊X返回所需的模型输出
    def forward(self, X):
        # 注意，这⾥我们使⽤ReLU的函数版本，其在nn.functional模块中定义。
        return self.out(F.relu(self.hidden(X)))


net = MLP()
print(net(X))


# 顺序块 Sequence

# 在向前传播函数中执行代码
class FixedHiddenMLP(nn.Module):
    def __init__(self):
        super().__init__()
        # 不计算梯度的随机权重参数。因此在训练期间保持不变
        self.rand_weight = torch.rand((20, 20), requires_grad=False)
        self.linear = nn.Linear(20, 20)

    def forward(self, X):
        X = self.linear(X)
        # 使用创建的常量参数以及relu和mm函数
        X = F.relu(torch.mm(X, self.rand_weight)+1)
        # 复用全连接层。相当于两个全连接层共享参数
        X = self.linear(X)
        # 控制流
        while X.abs().sum() > 1:
            X/2
        return X.sum()
