#include <iostream>
using namespace std;

//左移运算符重载

class Person
{
    friend ostream &operator<<(ostream &out, Person &p);

public:
    Person(int a, int b)
    {
        m_A = a;
        m_B = b;
    }

private:
    int m_A;
    int m_B;

    //利用成员函数重载 左移运算符 p.operator << (cout) 简化版本 p << cout;
    //通常不会利用成员函数重载 << 运算符 因为无法实现 cout在左侧
    // void operator<<(cout)
    // {
    // }
};

//只能利用全局函数重载左移运算符 <<
ostream &operator<<(ostream &out, Person &p) //本质 operator << (cout, p) 简化 cout << p
{
    out << "m_A = " << p.m_A << "  m_B = " << p.m_B;
    return out;
}

void test1()
{
    Person p(10, 20);

    cout << p << endl
         << "Hello World!";
}

int main()
{
    test1();

    return 0;
}