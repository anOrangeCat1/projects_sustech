#include <iostream>
using namespace std;

int add(int num1, int num2)
{
    // 函数定义的时候
    // num1 和 num2 并没有真实的数据 只是一个形式上的参数 简称形参
    int sum = num1 + num2;
    return sum;
}

int main()
{
    int a = 10;
    int b = 20;

    // a 和 b 称为 实际参数 简称实参
    // 当调用函数的时候 实参的值会传递给形参
    int c = add(a, b);

    cout << c;

    return 0;
}