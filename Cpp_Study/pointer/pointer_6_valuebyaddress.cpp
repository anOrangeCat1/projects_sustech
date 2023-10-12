#include <iostream>
using namespace std;

void swap1(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "swap1: x = " << a << endl;
    cout << "swap1: y = " << b << endl;
}

void swap2(int *p1, int *p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;

    cout << "swap2: *p1 = " << *p1 << endl;
    cout << "swap2: *p2 = " << *p2 << endl;
}

int main()
{
    //指针和函数
    // 1、值传递
    int x1 = 10;
    int y1 = 20;
    swap1(x1, y1);

    cout << "x1 = " << x1 << endl;
    cout << "y1 = " << y1 << endl;

    // 2、地址传递
    // 如果地址传递，可以改变实参
    int x2 = 10;
    int y2 = 20;

    swap2(&x2, &y2); //用指针接收地址

    cout << "x2 = " << x2 << endl;
    cout << "y2 = " << y2 << endl;

    return 0;
}