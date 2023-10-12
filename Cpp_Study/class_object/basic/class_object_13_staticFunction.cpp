#include <iostream>
using namespace std;

//静态成员函数
//所有对象共享同一函数
//静态成员函数只能访问静态成员变量
class Person
{
public:
    static int m_A; //静态成员变量
    int m_B;        //非静态成员变量

    //静态成员函数
    static void func()
    {
        cout << m_A << endl;

        m_A = 100; //静态成员函数可以访问 静态成员变量
        // m_B = 200; //静态成员函数不可以访问 非静态成员变量 无法区分到底是哪个对象的 m_B
        cout << "static void func()" << endl;
        cout << "m_A = " << m_A << endl;
    }

        //静态成员函数也有访问权限
private:
    static void func2()
    {
        cout << "static void func2()" << endl;
    }
};

int Person::m_A = 10;

void test1()
{
    //两种访问方式
    // 1. 通过对象访问
    Person p;
    p.func();

    // 2. 通过类名访问
    Person::func();

    // Person::func2(); //类外无法访问私有静态成员函数
}

int main()
{
    test1();

    return 0;
}