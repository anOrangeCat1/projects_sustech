#include <iostream>
using namespace std;

//多继承语法
// C++实际开发中不建议多继承

class Base1
{
public:
    int m_A;
    Base1()
    {
        m_A = 100;
    }
};

class Base2
{
public:
    int m_A;
    Base2()
    {
        m_A = 200;
    }
};

//子类 需要继承Base1和Base2
//语法: class 子类 : 继承方式 父类1, 继承方式 父类2 ...
class Son : public Base1, public Base2
{
public:
    int m_C;
    int m_D;
    Son()
    {
        m_C = 300;
        m_D = 400;
    }
};

void test1()
{
    cout << "size of Son: " << sizeof(Son) << endl;

    Son s;

    //当父类中出现同名成员 需要加作用域区分
    cout << "Base1: m_A = " << s.Base1::m_A << endl;
    cout << "Base2: m_A = " << s.Base2::m_A << endl;
}

int main()
{
    test1();

    return 0;
}