#include <iostream>
using namespace std;

//多态深入剖析

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

// vfptr 虚函数(表)指针 v-virtual  f-function  ptr-pointer
// vftable 虚函数表 表内记录虚函数的地址
// 子类继承父类vfptr 指向子类vftable 此时虚函数与父类一致
// 当子类重写父类的虚函数
// 子类中的虚函数表 内部 会替换 重写后的子类的虚函数表(覆盖)
// 当父类的指针或者引用指向子类对象时候 发生多态
// Animal & animal = cat;
// cat.speak; 此时调用 猫类 的虚函数表

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

void test2()
{
    cout << "size of Animal: " << sizeof(Animal) << endl;
}

int main()
{
    test1();
    test2();

    return 0;
}