#include <iostream>
using namespace std;

//交换函数
// 1.值传递
void swap1(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "swap1: a = " << a << endl;
    cout << "swap1: b = " << b << endl;
}

// 2.地址传递
void swap2(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 3.引用传递
void swap3(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a = 10;
    int b = 20;

    swap1(a, b); //值传递 形参不会修饰实参

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    swap2(&a, &b); //地址传递 形参会修饰实参

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    swap3(a, b); //引用传递 形参会修饰实参

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    //通过引用参数产生的效果和地址传递效果一样
    return 0;
}