#include <iostream>
using namespace std;

//递增运算符重载

/*
int a = 10;
cout << ++a << endl; // 11
cout << a<< endl; // 11

int b = 10;
cout << b++ << endl; // 10
cout << b << endl; // 11
*/

//自定义整型
class MyInteger
{
    friend ostream &operator<<(ostream &cout, MyInteger myint);

public:
    MyInteger()
    {
        m_Num = 0;
    }

    //重载 前置++ 运算符
    //返回引用是为了抑制对一个数据进行递增操作
    MyInteger &operator++()
    {
        //先进行++运算
        m_Num++;

        //再进行自身做返回
        return *this;
    }

    //重载 后置++ 运算符
    // MyInteger operator++(int)   int 代表占位参数 可以用于区分前置和后置递增
    MyInteger operator++(int)
    {
        //先 记录当时结果
        MyInteger temp = *this;

        //后 递增
        m_Num++;

        //最后 将记录结果做返回
        return temp;
    }

private:
    int m_Num;
};

//重载 << 运算符
ostream &operator<<(ostream &cout, MyInteger myint)
{
    cout << myint.m_Num;
    return cout;
}

void test1()
{
    MyInteger myint;

    cout << myint << endl;
    cout << ++(++myint) << endl;
    cout << myint << endl;
}

void test2()
{
    MyInteger myint;

    cout << myint++ << endl;
    cout << myint;
}

int main()
{
    test1();
    test2();

    return 0;
}