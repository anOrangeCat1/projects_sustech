#include <iostream>
using namespace std;

//空指针调用成员函数

class Person
{
public:
    int m_Age;

    void showClassName()
    {
        cout << "This is Person class." << endl;
    }

    void showPersonAge()
    {
        //传入指针是为NULL

        if (this == NULL)
        {
            return;
        }

        cout << "age = " << this->m_Age << endl;
    }
};

void test1()
{
    Person *p = NULL;

    p->showClassName();
    p->showPersonAge();
}

int main()
{
    test1();

    return 0;
}