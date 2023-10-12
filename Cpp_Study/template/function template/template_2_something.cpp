#include <iostream>
using namespace std;

//函数模板注意事项

template <typename T> // typename可以替换成class
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

// 1.自动类型推导 必须推导出一致的数据类型T才可以使用
void test1()
{
    int a = 10;
    int b = 20;

    mySwap(a, b); //正确

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    char c = 'c';

    // mySwap(a, c); //错误 int 和 char 不一致
    //推导不出一致的T类型
}

// 2.模板必须要确定出T的数据类型 才可以使用
template <typename T>
void func()
{
    cout << "func()" << endl;
}

void test2()
{
    func<int>(); //直接指定T的数据类型
}

int main()
{
    test1();
    test2();

    return 0;
}