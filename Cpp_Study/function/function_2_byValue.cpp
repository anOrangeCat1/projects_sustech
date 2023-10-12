#include <iostream>
using namespace std;

//值传递
//定义函数 实现两个数字进行交换的函数

void swap(int num1, int num2)
{
    cout << "before swap: " << endl;
    cout << "num1: " << num1 << "  num2: " << num2 << endl;

    int temp = num1;
    num1 = num2;
    num2 = temp;

    cout << "after swap: " << endl;
    cout << "num1: " << num1 << "  num2: " << num2 << endl;
}

int main()
{
    int a = 10;
    int b = 20;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    swap(a, b);

    //当我们做值传递时 函数的形参发生改变 并不会影响实参

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    return 0;
}