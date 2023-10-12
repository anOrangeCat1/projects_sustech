#include <iostream>
using namespace std;

//对象的初始化和清理
// 1. 构造函数 进行初始化操作
// 2. 析构函数 进行清理的操作

class Person
{
public:
    Person()
    {
        cout << "constructor of Person." << endl;
    }

    ~Person()
    {
        cout << "destructor of Person." << endl;
    }
};

void test1()
{
    Person p; //栈上的数据 test1执行完毕后 释放这个对象
}

int main()
{
    test1();
    Person p;

    return 0;
}