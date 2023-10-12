#include <iostream>
using namespace std;

//当模板碰到继承时 需要注意以下几点
/*
1. 当子类继承的父类是一个类模板时 子类在声明的时候 要制定出父类中T的类型
2. 如果不指定 编译器无法给子类分配内存
3. 如果想灵活指定出父类中T的类型 子类也需变为类模板
*/

//类模板与继承
template <class T>
class Base
{
    T m;
};

// class Son : public Base //错误 必须要知道父类中T的数据类型 才能继承给子类
class Son1 : public Base<int>
{
};

void test1()
{
    Son1 s1;
}

//如果想灵活指定父类中T的数据类型 子类也需要变模板类
template <class T1, class T2>
class Son2 : public Base<T2>
{
public:
    T1 obj;

    Son2()
    {
        cout << "T1: " << typeid(T1).name() << endl;
        cout << "T2: " << typeid(T2).name() << endl;
    }
};

void test2()
{
    Son2<int, char> s2;
}

int main()
{
    test1();
    test2();

    return 0;
}

//如果父类是类模板 子类需要指定出父类中T的数据类型