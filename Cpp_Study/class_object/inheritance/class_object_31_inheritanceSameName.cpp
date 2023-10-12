#include <iostream>
using namespace std;

//继承中同名成员处理
class Base
{
public:
    int m_A;
    Base()
    {
        m_A = 100;
    }

    void func()
    {
        cout << "Base : func()" << endl;
    }

    void func(int a)
    {
        cout << "Base : func(int a)" << endl;
    }
};

class Son : public Base
{
public:
    int m_A;
    Son()
    {
        m_A = 200;
    }

    void func()
    {
        cout << "Son : func()" << endl;
    }
};

//同名成员属性处理方式
void test1()
{
    Son s;
    cout << "Son: m_A = " << s.m_A << endl;

    //如果通过子类对象 访问到父类中的同名成员 需要加作用域
    cout << "Base: m_A = " << s.Base::m_A << endl;
}

//同名成员函数处理方式
void test2()
{
    Son s;

    s.func(); //直接调用 调用是子类中的同名成员

    //如何调用到父亲中同名成员函数?
    s.Base::func();

    //如果子类中出现了和父类同名的成员函数 子类的同名成员会隐藏掉父类中所有的成员
    //如果想访问到父类中被隐藏的同名成员函数 需要加作用域
    // s.func(100); 无法调用
    s.Base::func(100); //不论有参无参都要加作用域
}

int main()
{
    test1();
    test2();

    return 0;
}

/*
总结
1. 子类对象可以直接访问到子类中同名成员
2. 子类对象加作用域可以访问到父类同名成员
3. 当子类与父类拥有同名的成员函数 子类会隐藏父类中同名成员函数 加作用域可以访问到父类中同名函数

*/