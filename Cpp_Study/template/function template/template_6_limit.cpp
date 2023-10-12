#include <iostream>
using namespace std;
#include <string>

//模板的局限性
//模板的通用性不是万能的 有些特定的数据类型 需要用具体化方式做特殊实现

class Person
{
public:
    string m_Name;
    int m_Age;

    Person(string name, int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
};

//对比两个数据是否相等函数
template <class T>
bool myCompare(T &a, T &b)
{
    if (a == b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//利用具体化Person的版本实现代码 具体化优先调用
template <>
bool myCompare(Person &p1, Person &p2)
{
    if (p1.m_Name == p2.m_Name && p1.m_Age == p2.m_Age)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void test1()
{
    int a = 10;
    int b = 20;

    bool result = myCompare(a, b);

    if (result)
    {
        cout << "a == b" << endl;
    }
    else
    {
        cout << "a != b" << endl;
    }
}

void test2()
{
    Person p1("Tom", 10);
    Person p2("Tom", 11);

    bool result = myCompare(p1, p2);
    if (result)
    {
        cout << "p1 == p2" << endl;
    }
    else
    {
        cout << "p1 != p2" << endl;
    }
}

int main()
{
    test1();
    test2();

    return 0;
}

//学习模板并不是为了写模板 而是在STL能够运用系统提供的模板