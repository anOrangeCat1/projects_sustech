#include <iostream>
using namespace std;

//多态分为 静态多态 和 动态多态
//静态多态 函数重载 和 运算符重载 复用函数名
//动态多态 派生类 和 虚函数 实现运行时多态

//静态多态和动态多态区别
//静态多态的函数地址早绑定 编译阶段确定函数地址
//动态多态的函数地址晚绑定 运行阶段确定函数地址

//多态

//动物类
class Animal
{
public:
    //虚函数
    virtual void speak()
    {
        cout << "Animals speak" << endl;
    }
};

//猫类
class Cat : public Animal
{
public:
    void speak()
    {
        cout << "Cats speak" << endl;
    }
};

//狗类
class Dog : public Animal
{
public:
    void speak()
    {
        cout << "Dogs speak" << endl;
    }
};

//执行说话的函数
//地址早绑定 在编译阶段确定函数的地址
//如果想执行让猫说话 那么这个函数地址就不能提前绑定 需要在运行阶段进行绑定 地址晚绑定

//动态多态满足条件
// 1. 有继承关系
// 2. 子类重写父类的虚函数 注意 此处为重写而非重载
//重写 函数返回值类型 函数名 参数列表 完全相同

//动态多态使用
//父类的指针或者引用 执行子类的对象

void doSpeak(Animal &animal)
{
    animal.speak(); // Animal中的speak函数
}

void test1()
{
    Cat cat;
    doSpeak(cat); // Animal & animal = cat;

    Dog dog;
    doSpeak(dog);
}

int main()
{
    test1();

    return 0;
}