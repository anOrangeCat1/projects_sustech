#include <iostream>
using namespace std;

// C++泛型编程 STL
//模板就是建立通用的模具 大大提高复用性

//模板不可以直接使用 它只是一个框架
//模板的通用并不是万能的

// C++另一种编程思想称为 泛型编程 主要利用的技术就是模板
// C++提供两种模板机制: 函数模板 和 类模板

//函数模板语法
// template <typename T>

//函数模板

//交换两个整型函数

void swapInt(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//交换两个浮点型函数
void swapDouble(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
}

//函数模板
template <typename T> //声明一个模板 告诉编译器后面代码中紧跟着的 T 不要报错 T是一个通用数据类型
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

void test1()
{
    int a = 10;
    int b = 20;

    // swapInt(a, b);

    //利用函数模板交换
    //两种方式使用函数模板
    // 1. 自动类型推导
    mySwap(a, b);

    // 2. 显示指定类型
    mySwap<int>(a, b);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    double c = 1.1;
    double d = 2.2;

    swapDouble(c, d);
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
}

int main()
{
    test1();

    return 0;
}

//函数模板利用关键字 template
//使用函数模板有两种方式: 自动类型推导 显示指定类型
//模板的目的是为了提高复用性 将类型参数化