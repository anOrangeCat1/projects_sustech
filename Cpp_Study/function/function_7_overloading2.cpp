#include <iostream>
using namespace std;

//函数重载的注意事项
/*
1. 引用作为重载的条件
2. 函数重载碰到默认参数
*/

void func(int &a)
{
    cout << "func(int &a)" << endl;
}

void func(const int &a)
{
    cout << "func(const int &a)" << endl;
}

void func2(int a, int b = 10)
{
    cout << "func2(int a, int b)" << endl;
}

void func2(int a)
{
    cout << "func2(int a)" << endl;
}

int main()
{
    int a = 10;
    func(a); // func(int &a)

    const int b = 20;
    func(b); // func(const int &a)

    func(30); // func(const int &a)
    // int &a = 10 不合法
    // const int &a = 10 合法
    // 所以调用 func(const int &a)

    // func2(10); // wrong
    //当函数重载碰到默认参数 出现二义性 报错 需尽量避免这种情况

    func2(1, 2); // right

    return 0;
}