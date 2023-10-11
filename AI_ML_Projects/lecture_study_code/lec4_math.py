"""
--Some Math---

torch vector
tensor
torch viz (depends on graphviz)
make-dot(a.sum())

"""

import torch


def func1():
    x = torch.tensor(3.0)
    y = torch.tensor(2.0)

    print(x+y, x*y, x/y, x**y)


def func2():
    x = torch.arange(4)
    print(x, x[3])
    print(x.shape, len(x))


def func3():
    A = torch.arange(20).reshape(5, 4)
    print(A)
    print(A.T)

    B = torch.tensor([[1, 2, 3], [2, 0, 4], [3, 4, 5]])
    print(B)
    print(B == B.T)


def func4():
    X = torch.arange(24).reshape(2, 3, 4)
    print(X)


def func5():
    A = torch.arange(20, dtype=torch.float32).reshape(5, 4)
    B = A.clone()

    print(A)
    print(A+B)
    print(A*B)


def func6():
    a = 2
    X = torch.arange(24).reshape(2, 3, 4)

    print(a+X)
    print((a*X).shape)


def func7():
    x = torch.arange(4, dtype=torch.float32)

    print(x)
    print(x.sum())


def func8():
    A = torch.arange(20, dtype=torch.float32).reshape(5, 4)
    print(A)

    A_sum_axis0 = A.sum(axis=0)
    print(A_sum_axis0)
    print(A_sum_axis0.shape)

    A_sum_axis1 = A.sum(axis=1)
    print(A_sum_axis1)
    print(A_sum_axis1.shape)

    print(A.sum(axis=[0, 1]))  # as same as A.sum()
    print(A.mean(), A.sum()/A.numel())
    print(A.mean(axis=0), A.sum(axis=0)/A.shape[0])

    sum_A = A.sum(axis=1, keepdim=True)
    print(sum_A)
    print(A.cumsum(axis=0))
    print(A/sum_A)


def func9():
    x = torch.arange(4, dtype=torch.float32)
    y = torch.ones(4, dtype=torch.float32)
    A = torch.arange(20, dtype=torch.float32).reshape(5, 4)

    print(torch.dot(x, y))
    print(A)
    print(x)
    print(A.shape)
    print(x.shape)
    print(torch.mv(A, x))
    # print(torch.mv(x,A))  wrong!

    B = torch.ones(4, 3)
    print(torch.mm(A, B))


def func10():
    u = torch.tensor([3.0, -4.0])
    print(torch.norm(u))
    print(torch.abs(u).sum())

    print(torch.norm(torch.ones(4, 9)))


def f(x):
    return 3*x**2-4*x


def numerical_lim(f, x, h):
    return (f(x+h)-f(x))/h


def func11():
    h = 0.1
    for i in range(5):
        print(f'h={h:.5f},numerical limit={numerical_lim(f,1,h):.5f}')
        h *= 0.1


def func12():
    x = torch.arange(4.0)
    x.requires_grad_(True)
    y = 2*torch.dot(x, x)
    print(x, y)

    y.backward()
    print(x.grad)

    y = x.sum()
    y.backward
    print(x.grad)

    # PyTorch accumulates the gradient in default, we need to clear the previous.
    x.grad.zero_()
    y = x.sum()
    y.backward()
    print(x.grad)


def func13():
    x = torch.arange(4.0)
    x.requires_grad_(True)
    y = x * x
    z = y * x
    z.sum().backward()
    print(x.grad == 3*x*x)

    x.grad.zero_()
    y = x * x
    u = y.detach()
    z = u * x
    z.sum().backward()
    print(x.grad == u)


def func14():
    fair_probs = torch.ones([6])/6
    print(torch.distributions.multinomial.Multinomial(1, fair_probs).sample())

    fair_probs = torch.ones([6])/6
    print(torch.distributions.multinomial.Multinomial(10, fair_probs).sample())

    counts = torch.distributions.multinomial.Multinomial(
        1000, fair_probs).sample()
    print(counts/1000)  # Relative frequecy as the estimate


def func15():
    print(dir(torch.distributions))


if __name__ == "__main__":
    # func1()
    # func2()
    # func3()
    # func4()
    # func5()
    # func6()
    # func7()
    # func8()
    # func9()
    # func10()
    # func11()
    # func12()
    # func13()
    # func14()
    func15()
