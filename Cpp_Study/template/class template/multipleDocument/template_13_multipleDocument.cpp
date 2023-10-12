#include <iostream>
using namespace std;

//第一种解决方式 直接接包含源文件
//#include "person.cpp"

//第二种解决方式 将.h和.cpp中内容写到一起 将后缀名改为.hpp文件
#include "person.hpp"

//类模板份文件编写问题以及解决

// template <class T1, class T2>
// class Person
// {
// public:
//     T1 m_Name;
//     T2 m_Age;



//     Person(T1 name, T2 age);

//     void showPerson();
// };

// template <class T1, class T2>
// Person<T1, T2>::Person(T1 name, T2 age)
// {
//     this->m_Name = name;
//     this->m_Age = age;
// }

// template <class T1, class T2>
// void Person<T1, T2>::showPerson()
// {
//     cout << "Name: " << this->m_Name << "  Age: " << this->m_Age << endl;
// }

void test1()
{
    Person<string, int> p("Mike", 18);
    p.showPerson();
}

int main()
{
    test1();

    return 0;
}