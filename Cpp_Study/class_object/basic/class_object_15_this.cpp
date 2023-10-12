#include <iostream>
using namespace std;

// this指针

// 1. 解决名称冲突

// 2. 返回对象本身用 *this

class Person
{
public:
    int age;

    Person(int age)
    {
        this->age = age;
    }

    // this 指针指向被调用的成员函数所属的对象

    // Person PersonAddAge(Person &p){...} 创建新的对象
    // Person &PersonAddAge(Person &p){...} 引用返回 返回本身
    Person &PersonAddAge(Person &p)
    {
        this->age += p.age;

        // this 是指向p2的指针 而*this指向的就是p2这个对象本体
        return *this;
    }
};

void test1()
{
    Person p1(18);
    cout << "age of p1: " << p1.age << endl;
}

void test2()
{
    Person p1(10);
    Person p2(10);
    p2.PersonAddAge(p1);

    cout << "age of p2: " << p2.age << endl;

    //链式编程思想
    p2.PersonAddAge(p1).PersonAddAge(p1).PersonAddAge(p1);

    cout << "age of p2: " << p2.age << endl;
}

int main()
{
    test2();

    return 0;
}