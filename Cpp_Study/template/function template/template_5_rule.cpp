#include <iostream>
using namespace std;

//普通函数和函数模板的调用规则
/*
1. 如果函数模板和普通函数都可以调用 优先调用普通函数
2. 可以通过空模板参数列表 强制调用 函数模板
3. 函数模板可以发生函数模板
4. 如果函数模板可以产生更好的匹配 优先调用函数模板
*/

void myPrint(int a, int b)
{
    cout << "normal func" << endl;
}

template <typename T>
void myPrint(T a, T b)
{
    cout << "template func" << endl;
}

template <typename T>
void myPrint(T a, T b, T c)
{
    cout << "template func overloading" << endl;
}

void test1()
{
    int a = 10;
    int b = 10;

    myPrint(a, b);

    //通过空模板参数列表 强制调用函数模板
    myPrint<>(a, b);

    myPrint(a, b, 100);

    char c1 = 'a';
    char c2 = 'b';

    myPrint(c1, c2);
}

int main()
{
    test1();

    return 0;
}

//总结 既然提供了函数模板 最好就不要提供普通函数 否则容易出现二义性