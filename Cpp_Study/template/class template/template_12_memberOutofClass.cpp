#include <iostream>
using namespace std;

//类模板成员函数类外实现
template <class T1, class T2>
class Person
{
public:
    T1 m_Name;
    T2 m_Age;

    Person(T1 name, T2 age);
    // {
    //     this->m_Name = name;
    //     this->m_Age = age;
    // }

    void showPerson();
    // {
    //     cout << "Name: " << this->m_Name << "  Age: " << this->m_Age << endl;
    // }
};

//构造函数类外实现
template <class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
    this->m_Name = name;
    this->m_Age = age;
}

//成员函数的类外实现
template <class T1, class T2>
void Person<T1, T2>::showPerson()
{
    cout << "Name: " << this->m_Name << "  Age: " << this->m_Age << endl;
}

void test1()
{
    Person<string, int> p("Tom", 20);
    p.showPerson();
}

int main()
{
    test1();

    return 0;
}

//类模板中成员函数类外实现时 需要加上模板参数列表