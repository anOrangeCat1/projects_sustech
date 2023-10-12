#include <iostream>
using namespace std;

//类模板配合友元函数的类内和类外实现
//全局函数类内实现 直接在类内声明友元即可
//全局函数类外实现 需要提前让编译器知道全局函数的存在

//提前让编译器知道Person类存在
template <class T1, class T2>
class Person;

//类外实现
template <class T1, class T2>
void printPerson2(Person<T1, T2> p)
{
    cout << "Out of class: Name: " << p.m_Name << "  Age: " << p.m_Age << endl;
}

template <class T1, class T2>
class Person
{
    //全局函数　类内实现
    friend void printPerson(Person<T1, T2> p)
    {
        cout << "In class: Name: " << p.m_Name << "  Age: " << p.m_Age << endl;
    }

    //全局函数类外实现
    //加空模板参数列表
    //如果全局函数是类外实现 需要让编译器提前知道这个函数的存在
    friend void printPerson2<>(Person<T1, T2> p);

private:
    T1 m_Name;
    T2 m_Age;

public:
    Person(T1 name, T2 age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
};

// 1. 全局函数在类内实现
void test1()
{
    Person<string, int> p("Tom", 20);

    printPerson(p);
}

// 2. 全局函数在类外实现
void test2()
{
    Person<string, int> p("Jerry", 18);

    printPerson2(p);
}

int main()
{
    test1();
    test2();

    return 0;
}

//建议全局函数做类内实现 用法简单 而且编译器可以直接识别