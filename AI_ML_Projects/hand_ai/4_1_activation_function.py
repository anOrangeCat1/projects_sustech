import torch
from d2l import torch as d2l
import matplotlib.pyplot as plt

# ReLU
# ReLU(x) = max(x,0)
x = torch.arange(-8.0, 8.0, 0.1, requires_grad=True)
y = torch.relu(x)

d2l.plot(x.detach(),y.detach(),'x','y=relu(x)',figsize=(5,2))


# detach() 仅仅使requires_grad=False
plt.plot(x.detach(), y.detach())
plt.xlabel('x'), plt.ylabel('relu(x)')
plt.grid()
plt.show()

# ReLU的导数
y.backward(torch.ones_like(x), retain_graph=True)
plt.plot(x.detach(), x.grad)
plt.xlabel('x'), plt.ylabel("grad of relu")
plt.grid()
plt.show()


# sigmoid
y = torch.sigmoid(x)
plt.plot(x.detach(), y.detach())
plt.xlabel('x'), plt.ylabel('sigmoid(x)')
plt.grid()
plt.show()

# sigmoid的导数
# 清除以前的梯度
x.grad.data.zero_()
y.backward(torch.ones_like(x), retain_graph=True)
plt.plot(x.detach(), x.grad)
plt.xlabel('x'), plt.ylabel("grad of sigmoid")
plt.grid()
plt.show()


# tanh
y = torch.tanh(x)
plt.plot(x.detach(), y.detach())
plt.xlabel('x'), plt.ylabel('tanh(x)')
plt.grid()
plt.show()

# tanh的导数
# 清除以前的梯度
x.grad.data.zero_()
y.backward(torch.ones_like(x), retain_graph=True)
plt.plot(x.detach(), x.grad)
plt.xlabel('x'), plt.ylabel("grad of tanh")
plt.grid()
plt.show()
