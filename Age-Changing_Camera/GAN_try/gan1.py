import torch
import torch.nn as nn
import numpy as np
import matplotlib.pyplot as plt

# 定义生成器网络
class Generator(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(Generator, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, hidden_size)
        self.fc3 = nn.Linear(hidden_size, output_size)
        self.activation = nn.ReLU()

    def forward(self, x):
        out = self.activation(self.fc1(x))
        out = self.activation(self.fc2(out))
        out = self.fc3(out)
        return out

# 定义判别器网络
class Discriminator(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(Discriminator, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, hidden_size)
        self.fc3 = nn.Linear(hidden_size, output_size)
        self.activation = nn.ReLU()

    def forward(self, x):
        out = self.activation(self.fc1(x))
        out = self.activation(self.fc2(out))
        out = torch.sigmoid(self.fc3(out))
        return out

# 定义超参数
input_size = 1
hidden_size = 32
output_size = 1
lr = 0.001
batch_size = 128
epochs = 10000

# 定义模型、优化器和损失函数
G = Generator(input_size, hidden_size, output_size)
D = Discriminator(input_size, hidden_size, output_size)
G_optimizer = torch.optim.Adam(G.parameters(), lr=lr)
D_optimizer = torch.optim.Adam(D.parameters(), lr=lr)
criterion = nn.BCELoss()

# 生成真实数据和噪声数据
def generate_real_data(n):
    x = np.random.normal(4, 1, n)
    return torch.from_numpy(x).float().view(-1, 1)

def generate_noise_data(n):
    x = np.random.normal(0, 1, n)
    return torch.from_numpy(x).float().view(-1, 1)

# 开始训练
for epoch in range(epochs):
    # 训练判别器
    real_data = generate_real_data(batch_size)
    noise_data = generate_noise_data(batch_size)
    G_output = G(noise_data)
    D_real_loss = criterion(D(real_data), torch.ones(batch_size, 1))
    D_fake_loss = criterion(D(G_output), torch.zeros(batch_size, 1))
    D_loss = D_real_loss + D_fake_loss
    D_optimizer.zero_grad()
    D_loss.backward()
    D_optimizer.step()

    # 训练生成器
    noise_data = generate_noise_data(batch_size)
    G_output = G(noise_data)
    D_fake_loss = criterion(D(G_output), torch.ones(batch_size, 1))
    G_loss = D_fake_loss
    G_optimizer.zero_grad()
    G_loss.backward()
    G_optimizer.step()

    # 打印训练结果
    if epoch % 1000 == 0:
        print('Epoch [{}/{}], D_loss: {:.4f}, G_loss: {:.4f}'.format(epoch, epochs, D_loss.item(), G_loss.item()))


