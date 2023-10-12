#include <iostream>
using namespace std;

//拷贝构造函数的调用时机

// 1. 使用一个已经创建完毕的对象来初始化一个新对象
// 2. 值传递的方式给函数参数传值
// 3. 值方式返回局部对象

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

// 1. 使用一个已经创建完毕的对象来初始化一个新对象
void test1()
{
    Person p1(20);
    Person p2(p1);
}

// 2. 值传递的方式给函数参数传值
void doWork1(Person p){};

void test2()
{
    Person p;
    doWork1(p); //此处调用 拷贝构造函数
}

// 3. 值方式返回局部对象 //mingw并未copy
Person doWork2()
{
    Person p1;
    cout << (int *)&p1 << endl;
    return p1;
}

void test3()
{
    Person p = doWork2();
    cout << (int *)&p << endl;
}

int main()
{
    test1();
    test2();
    test3();

    return 0;
}