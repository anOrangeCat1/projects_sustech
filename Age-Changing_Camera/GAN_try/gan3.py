import torch
import torch.nn as nn
import torch.optim as optim
import torchvision.datasets as datasets
import torchvision.transforms as transforms
import torchvision.utils as vutils

# 定义生成器


class Generator(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(Generator, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, hidden_size)
        self.fc3 = nn.Linear(hidden_size, output_size)
        self.relu = nn.ReLU()

    def forward(self, x):
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.fc3(x)
        return x

# 定义判别器


class Discriminator(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(Discriminator, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, hidden_size)
        self.fc3 = nn.Linear(hidden_size, output_size)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        x = self.sigmoid(self.fc1(x))
        x = self.sigmoid(self.fc2(x))
        x = self.sigmoid(self.fc3(x))
        return x


# 定义超参数
input_size = 100
hidden_size = 256
output_size = 784
num_epochs = 100
batch_size = 100
learning_rate = 0.001

# 加载MNIST数据集
train_dataset = datasets.MNIST(
    root='./data', train=True, transform=transforms.ToTensor(), download=True)
train_loader = torch.utils.data.DataLoader(
    dataset=train_dataset, batch_size=batch_size, shuffle=True)

# 初始化生成器和判别器
generator = Generator(input_size, hidden_size, output_size)
discriminator = Discriminator(output_size, hidden_size, 1)

# 定义损失函数和优化器
criterion = nn.BCELoss()
optimizer_g = optim.Adam(generator.parameters(), lr=learning_rate)
optimizer_d = optim.Adam(discriminator.parameters(), lr=learning_rate)

# 开始训练
for epoch in range(num_epochs):
    for i, (real_images, _) in enumerate(train_loader):
        # 训练判别器
        discriminator.zero_grad()
        real_images = real_images.view(-1, 28 * 28)
        real_labels = torch.ones(batch_size, 1)
        fake_labels = torch.zeros(batch_size, 1)
        z = torch.randn(batch_size, input_size)
        fake_images = generator(z)
        outputs_real = discriminator(real_images)
        outputs_fake = discriminator(fake_images)
        loss_d_real = criterion(outputs_real, real_labels)
        loss_d_fake = criterion(outputs_fake, fake_labels)
        loss_d = loss_d_real + loss_d_fake
        loss_d.backward()
        optimizer_d.step()

        # 训练生成器
        generator.zero_grad()
        z = torch.randn(batch_size, input_size)
        fake_images = generator(z)
        outputs = discriminator(fake_images)
        loss_g = criterion(outputs, real_labels)
        loss_g.backward()
        optimizer_g.step()

        if (i + 1) % 100 == 0:
            print(loss_g, loss_d)

# 生成新图片进行验证
# num_test_images = 16
# z = torch.randn(num_test_images, input_size)
# fake_images = generator(z)
# fake_images = fake_images.reshape(-1, 1, 28, 28)
# vutils.save_image(fake_images, './generated_images.png', normalize=True)

for i in range(10):
    num_test_images = 16
    z = torch.randn(num_test_images, input_size)
    fake_images = generator(z)
    fake_images = fake_images.reshape(-1, 1, 28, 28)
    vutils.save_image(fake_images, './generated_images.png'+i, normalize=True)
