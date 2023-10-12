#include <iostream>
using namespace std;

//初始化列表
//语法 构造函数():属性1(值1), 属性2(值2) ... {}

class Person
{
public:
    int m_A;
    int m_B;
    int m_C;

    //传统初始化操作
    // Person(int a, int b, int c)
    // {
    //     m_A = a;
    //     m_B = b;
    //     m_C = c;
    // }

    //初始化列表初始化属性
    Person() : m_A(10), m_B(20), m_C(30) {}
    Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c) {}
};

void test1()
{
    Person p(30, 20, 10);
    cout << "m_A: " << p.m_A << endl;
    cout << "m_B: " << p.m_B << endl;
    cout << "m_C: " << p.m_C << endl;
}

int main()
{
    test1();

    return 0;
}