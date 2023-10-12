#include <iostream>
using namespace std;

//构造函数的调用规则

// 1. 创建一个类 C++编译器会给每个类添加至少3个函数
//默认构造 空实现
//析构函数 空实现
//拷贝函数 值拷贝

// 2. 调用规则
//如果我们写了有参构造函数 编译器就不再提供默认构造 但依然提供拷贝构造
//如果我们写了拷贝构造函数 编译器就不再提供其他的构造函数

class Person
{
public:
    int age;

    Person()
    {
        cout << "default constructor" << endl;
    }

    Person(int a)
    {
        age = a;
        cout << "parameter constructor" << endl;
    }

    Person(const Person &p)
    {
        age = p.age;
        cout << "copy constructor" << endl;
    }

    ~Person()
    {
        cout << "destructor" << endl;
    }
};

void test1()
{
    Person p;
    p.age = 18;
    Person p2(p);

    cout << "age of p2: " << p2.age << endl;
}

int main()
{
    test1();

    return 0;
}