import random
import torch
import matplotlib.pyplot as plt

# w = [2,-3,4]T, b = 4.2
# y = Xw + b + n


def synthetic_data(w, b, num_examples):
    """
    生成 y=Xw+b 噪声n
    可以视为模型预测和标签时的潜在观察误差
    """
    # torch.normal(mean,std,size)
    X = torch.normal(0, 1, (num_examples, len(w)))
    # print(X.shape)
    y = torch.matmul(X, w)+b
    y += torch.normal(0, 0.01, y.shape)
    return X, y.reshape((-1, 1))


true_w = torch.tensor([2, -3.4])
true_b = 4.2
features, lables = synthetic_data(true_w, true_b, 1000)
# features 的维度是 2维
print('features:', features[0], '\nlable:', lables[0])
# 生成第二个特征features[:,1]和lables散点图，可以直观观察到两者之间的线性关系
plt.plot(features[:, 1], lables, 'o')
plt.show()


def data_iter(batch_size, features, labels):
    """
    训练模型时要对数据集进⾏遍历，每次抽取⼀⼩批量样本，
    并使⽤它们来更新我们的模型。由于这个过程是训练机器学习算法的基础，
    所以有必要定义⼀个函数，该函数能打乱数据集中的样本并以⼩批量⽅式
    获取数据。
    ===========================================================
    当我们运⾏迭代时，我们会连续地获得不同的⼩批量，
    直⾄遍历完整个数据集。上⾯实现的迭代对于教学来说很好，
    但它的执⾏效率很低，可能会在实际问题上陷⼊⿇烦。
    ================================================
    在深度学习框架中实现的内置迭代器效率要⾼得多
    ===========================================================
    此函数接收批量⼤⼩、特征矩阵和标签向量作为输⼊，
    ⽣成⼤⼩为batch_size的⼩批量。每个⼩批量包含⼀组特征和标签。
    """
    num_examples = len(features)
    indices = list(range(num_examples))
    # indice = index
    # 这些样本是随机读取的，没有特定顺序
    random.shuffle(indices)
    # random.shuffle()用于将一个列表中的元素打乱顺序
    # 值得注意的是使用这个方法不会生成新的列表，只是将原列表的次序打乱。
    for i in range(0, num_examples, batch_size):
        batch_indices = torch.tensor(
            indices[i:min(i+batch_size, num_examples)])
        yield features[batch_indices], labels[batch_indices]


batch_size = 10
for X, y in data_iter(batch_size, features, lables):
    print(X, '\n', y)
    break

# 初始化模型参数
"""
在初始化参数之后，我们的任务是更新这些参数，
直到这些参数⾜够拟合我们的数据
每次更新都需要计算损失函数关于模型参数的梯度，进行梯度下降
"""
w = torch.normal(0, 0.01, size=(2, 1), requires_grad=True)
b = torch.zeros(1, requires_grad=True)


# 定义模型
def linreg(X, w, b):
    """线性回归模型"""
    return torch.matmul(X, w)+b


# 定义损失函数
def squared_loss(y_hat, y):
    """均方损失"""
    return (y_hat-y.reshape(y_hat.shape))**2/2


# 定义优化算法
def sgd(params,lr,batch_size):
    """小批量随机梯度下降
    lr 学习率
    batch_size 规范化步长 这样步长大小就不会取决于我们对批量大小的选择
    """
    with torch.no_grad():
        # 在该模块下，所有计算得出的tensor的requires_grad都自动设置为False。
        # 节约内存和资源
        for param in params:
            param -= lr*param.grad/batch_size
            param.grad.zero_()
            

# 训练
lr = 0.03
num_epochs = 3
net = linreg
loss = squared_loss

for epoch in range(num_epochs):
    for X,y in data_iter(batch_size,features,lables):
        l = loss(net(X,w,b),y) # X和y的小批量损失
        # 因为l的形状是(batch_size, l),而不是一个标量。
        # l中的所有元素被加到一起，并以此计算关于[w,b]的梯度
        l.sum().backward()
        sgd([w,b],lr,batch_size) # 使用参数的梯度更新参数
    with torch.no_grad():
        train_l = loss(net(features,w,b),lables)
        print(f'epoch{epoch+1},loss{float(train_l.mean()):f}')
        
print(f'w的估计误差：{true_w-w.reshape(true_w.shape)}')
print(f'b的估计误差：{true_b-b}')
    
