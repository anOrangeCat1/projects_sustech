#include <iostream>
using namespace std;

//常函数

class Person
{
public:
    int m_A;
    mutable int m_B; // 特殊变量 即使在常函数中 也可以修改这个值 加关键字 mutable

    // this 指针的本质 是指针常量 指针的指向是不可以修改的
    // Person *const this;
    // const Person *const this;
    // 在成员函数后面加 const 修饰 this指针 让指针指向的值也不可以修改

    void showPerson() const
    {
        // this = NULL; this 指针不可以修改指针的指向
        // this->m_A = 100; 常函数中 this指针指向的值也不可以修改
        this->m_B = 100;
    }

    void func()
    {
        m_A = 100;
    }

    Person() {}
};

void test1()
{
    Person p;
    p.showPerson();
}

//常对象

void test2()
{
    const Person p; // 在对象前加const 变为常对象
    // p.m_A = 100;
    p.m_B = 100; // m_B是特殊值 在常对象下也可以修改

    // 常对象只能调用常对象
    p.showPerson();
    // p.func(); // 常对象 不可以调用普通成员函数 因为普通成员函数可以修改属性
}

int main()
{

    return 0;
}