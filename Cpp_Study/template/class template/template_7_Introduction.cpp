#include <iostream>
using namespace std;
#include <string.h>

//类模板

template <class NameType, class AgeType>
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

void test1()
{
    Person<string, int> p1("Tom", 999);
    p1.showPerson();
}

int main()
{
    test1();

    return 0;
}