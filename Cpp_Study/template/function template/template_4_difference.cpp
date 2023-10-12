#include <iostream>
using namespace std;

/*
普通函数与函数模板区别
1. 普通函数调用时可以发生自动类型转换(隐式类型转换)
2. 函数模板调用时 如果利用自动类型推导 不会发生隐式类型转换
3. 如果利用显示指定类型的方式 可以发生隐式类型转换
*/

//普通函数与函数模板的区别

//普通函数
int myAdd1(int a, int b)
{
    return a + b;
}

//函数模板
template <typename T>
T myAdd2(T a, T b)
{
    return a + b;
}

void test1()
{
    int a = 10;
    int b = 20;
    char c = 'c'; // a - 97 => c - 99

    cout << myAdd1(a, b) << endl;

    // 1. 普通函数调用可以发生隐式类型转换
    cout << myAdd1(a, c) << endl;

    //自动类型推导 不会发生隐式类型转换
    cout << myAdd2(a, b) << endl;
    // 2. 函数模板 用自动类型推导 不可以发生隐式类型转换
    // cout << myAdd2(a, c) << endl;

    //显示指定类型 会发生隐式类型转换
    // 3. 函数模板 用显示指定类型 可以发生隐式类型转换
    cout << myAdd2<int>(a, c) << endl;
}

int main()
{
    test1();

    return 0;
}