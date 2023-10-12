#include <iostream>
using namespace std;

//成员变量和成员函数分开存储

class Person
{
    int m_A; //非静态成员变量

    static int m_B; //静态成员变量 不属于类对象上

    void func() {} //非静态成员函数 不属于类对象上

    static void func2() {} //静态成员函数 不属于类对象上
};

void test1()
{
    Person p;
    // 空对象占用的内存空间为: 1
    // C++编译器会给每个对象也分配一个字节空间 是为了区分空对象占用内存的位置
    // 每个空对象也应该有一个独一无二的内存地址
    cout << "size of p = " << sizeof(p) << endl;
}

//只有非静态成员变量属于类对象

int main()
{
    test1();

    return 0;
}