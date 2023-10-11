import numpy as np
import torch
from torch.utils import data
import matplotlib.pyplot as plt
from d2l import torch as d2l

# 生成数据集
true_w = torch.tensor([2, -3.4])
true_b = 4.2
features, lables = d2l.synthetic_data(true_w, true_b, 1000)


# 读取数据集
def load_array(data_arrays, batch_size, is_train=True):
    """构造一个Pytorch数据迭代器"""
    dataset = data.TensorDataset(*data_arrays)
    return data.DataLoader(dataset, batch_size, shuffle=is_train)


batch_size = 10
data_iter = load_array((features,lables),batch_size)


# 定义模型
from torch import nn 

# fully-connected layer 全连接层
# 在PyTorch中，全连接层在Linear类中定义
# 两个参数传递到nn.Linear中：第⼀个指定输⼊特征形状，即2
# 第⼆个指定输出特征形状，输出特征形状为单个标量，因此为1
net = nn.Sequential(nn.Linear(2,1))


# 初始化参数模型
# 使⽤weight.data和bias.data⽅法访问参数
net[0].weight.data.normal_(0,0.01)
net[0].bias.data.fill_(0)


# 定义损失函数
# 计算均⽅误差使⽤的是MSELoss类，也称为平⽅L2范数。
# 默认情况下，它返回所有样本损失的平均值。
loss = nn.MSELoss()

# 定义优化算法
trainer = torch.optim.SGD(net.parameters(),lr=0.03)


# 训练
"""
对于每个小批量，进行以下步骤：
1. 通过调⽤net(X)⽣成预测并计算损失l(前向传播)
2. 通过进⾏反向传播来计算梯度
3. 通过调⽤优化器来更新模型参数
"""
num_epochs = 3
for epoch in range(num_epochs):
    for X,y in data_iter:
        l = loss(net(X),y)
        trainer.zero_grad()
        l.backward()
        trainer.step()
    l = loss(net(features),lables)
    print(f'epoch {epoch+1} ,loss {l:f}')

w = net[0].weight.data
print('w的估计误差: ',true_w-w.reshape(true_w.shape))
b = net[0].bias.data
print('b的估计误差: ',true_b-b)