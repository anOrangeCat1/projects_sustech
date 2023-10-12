#include <iostream>
using namespace std;

//纯虚函数
//语法 virtual 返回值类型 函数名 (参数列表) = 0;
//当类中有了纯虚函数 这个类称为抽象类

//抽象类特点
// 1.无法实例化对象
// 2.子类必须重写抽象类中的纯虚函数 否则也属于抽象类

//纯虚函数和抽象类
class Base
{
public:
    //纯虚函数
    //只要有一个纯虚函数 这个类属于抽象类
    //抽象类特点:
    // 1.无法实例化对象
    // 2.子类必须重写抽象类中的纯虚函数 否则也属于抽象类
    virtual void func() = 0;
};

class Son : public Base
{
public:
    virtual void func()
    {
        cout << "func()" << endl;
    }
};

void test1()
{
    //抽象类无法实例化对象
    // Base b;
    // new Base;

    Son s; //子类必须重写抽象类中的纯虚函数 否则无法实例化对象

    Base *base = new Son;
    base->func();
}

int main()
{
    test1();

    return 0;
}