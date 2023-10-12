#include <iostream>
using namespace std;
#include <string.h>

//类模板对象做函数参数
/*
1. 指定传入类型
2. 参数模板化
3. 整个类模板化
*/

template <class T1, class T2>
class Person
{
public:
    T1 m_Name;
    T2 m_Age;

    Person(T1 name, T2 age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }

    void showPerson()
    {
        cout << "Name: " << this->m_Name << "  Age: " << this->m_Age << endl;
    }
};

// 1.指定传入类型
void printPerson1(Person<string, int> &p)
{
    p.showPerson();
}

void test1()
{
    Person<string, int> p("Tom", 100);
    printPerson1(p);
}

// 2.参数模板化
template <class T1, class T2>
void printPerson2(Person<T1, T2> &p)
{
    p.showPerson();
    cout << "T1: " << typeid(T1).name() << endl;
    cout << "T2: " << typeid(T2).name() << endl;
}

void test2()
{
    Person<string, int> p("Mike", 90);
    printPerson2(p);
}

// 3.将整个类模板化
template <class T>
void printPerson3(T &p)
{
    p.showPerson();
    cout << "T: " << typeid(T).name() << endl;
}

void test3()
{
    Person<string, int> p("Jack", 30);
    printPerson3(p);
}

int main()
{
    test1();
    test2();
    test3();

    return 0;
}

//通过类模板创建的对象 可以有三种方式向函数中进行传参
//使用比较广泛的是第一种 指定传入的类型