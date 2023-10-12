#include <iostream>
using namespace std;

template <class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
    this->m_Name = name;
    this->m_Age = age;
}

template <class T1, class T2>
void Person<T1, T2>::showPerson()
{
    cout << "Name: " << this->m_Name << "  Age: " << this->m_Age << endl;
}

template <class T1, class T2>
class Person
{
public:
    T1 m_Name;
    T2 m_Age;

    Person(T1 name, T2 age);

    void showPerson();
};