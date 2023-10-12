#include <iostream>
using namespace std;

//函数重载
//可以让函数名相同 提高复用性

//函数重载的满足条件
/*
1. 同一作用域下
2. 函数名称相同
3. 函数参数 类型不同 或者 个数不同 或者 顺序不同
*/
//注意事项 函数的返回值不可以作为函数重载的条件

void func()
{
    cout << "func()" << endl;
}

void func(int a)
{
    cout << "func(int a)" << endl;
}

void func(double a)
{
    cout << "func(double a)" << endl;
}

void func(int a, double b)
{
    cout << "func(int a, double b)" << endl;
}

void func(double a, int b)
{

    cout << "func(double a, int b)" << endl;
}

int main()
{
    func();
    func(10);
    func(3.14);
    func(10, 3.14);
    func(3.14, 10);

    return 0;
}