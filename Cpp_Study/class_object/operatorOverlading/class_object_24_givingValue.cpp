#include <iostream>
using namespace std;

// C++编译器至少给一个类添加4个函数
/*
1. 默认构造函数(无参, 函数体为空)
2. 默认析构函数(无参, 函数体为空)
3. 默认拷贝函数 对属性进行值拷贝
4. 赋值运算符 operator= 对属性进行值拷贝
*/

//赋值运算符重载

class Person
{
public:
    int *m_Age;

    Person(int age)
    {
        m_Age = new int(age);
    }

    ~Person()
    {
        if (m_Age != NULL)
        {
            delete m_Age;
            m_Age = NULL;
        }
    }

    //重载 赋值运算符
    Person &operator=(const Person &p)
    {
        //编译器提供浅拷贝
        // m_Age = p.m_Age

        //应该先判断是否有属性在堆区 如果有 先释放干净 然后在深拷贝
        if (m_Age != NULL)
        {
            delete m_Age;
            m_Age = NULL;
        }

        //深拷贝
        m_Age = new int(*p.m_Age);

        //返回对象指针
        return *this;
    }
};

void test1()
{
    Person p1(18);

    Person p2(20);

    Person p3(30);

    p3 = p2 = p1; //赋值操作

    cout << "Age of p1: " << *p1.m_Age << endl;

    cout << "Age of p2: " << *p2.m_Age << endl;

    cout << "Age of p3: " << *p3.m_Age << endl;
}

int main()
{
    test1();

    return 0;
}