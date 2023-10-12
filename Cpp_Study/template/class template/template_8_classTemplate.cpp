#include <iostream>
using namespace std;
#include <string.h>

//类模板与函数模板区别
template <class NameType, class AgeType = int>
class Person
{
public:
    NameType m_Name;
    AgeType m_Age;

    Person(NameType name, AgeType age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }

    void showPerson()
    {
        cout << "Name: " << this->m_Name << "  Age: " << this->m_Age << endl;
    }
};

// 1.类模板没有自动类型推导使用方式
void test1()
{
    // Person p("Tom", 1000); 错误 无法用自动类型推导
    Person<string, int> p("Tom", 1000);
    p.showPerson();
}

// 2.类模板在模板参数列表中可以有默认参数
void test2()
{
    Person<string> p("Mike", 999);
    p.showPerson();
}

int main()
{
    test1();
    test2();

    return 0;
}