#include <iostream>
using namespace std;
#include <string.h>

//虚析构和纯虚析构

class Animal
{
public:
    Animal()
    {
        cout << "Constructor of Animal" << endl;
    }

    //纯虚函数
    virtual void speak() = 0;

    //虚析构
    // virtual ~Animal()
    // {
    //     cout << "Deconstructor of Animal: virtual" << endl;
    // }

    //纯虚析构 调用时必须要有具体实现
    virtual ~Animal() = 0;

    //纯虚函数 不需要有实现 子类需要重写
    //纯虚析构 需要声明也需要有实现
    //有了纯虚析构之后 这个类也属于抽象类 无法实例化对象
};

Animal::~Animal()
{
    cout << "Deconstructor of Animal: absolutly virtual" << endl;
}

class Cat : public Animal
{
public:
    string *m_Name;

    virtual void speak()
    {
        cout << *m_Name << " Cat speak" << endl;
    }

    Cat(string name)
    {
        cout << "Constructor of Cat" << endl;
        m_Name = new string(name);
    }

    ~Cat()
    {
        if (m_Name != NULL)
        {
            cout << "Destructor of Cat" << endl;
            delete m_Name;
            m_Name = NULL;
        }
    }
};

void test1()
{
    Animal *animal = new Cat("Tom");
    animal->speak();

    //父类指针在析构的时候 不会调用子类中析构函数 导致子类如果有堆区属性 就会出现内存泄露
    delete animal;
}

int main()
{
    test1();

    return 0;
}

//虚析构和纯虚析构共性
/*
1.可以解决父类指针释放子类对象的问题 如果没有虚析构或者纯虚析构 无法调用子类的析构函数
2.都需要有具体的函数实现
*/

//虚析构和纯虚析构区别：
//如果是纯虚析构 该类属于抽象类 无法实例化对象
//虚析构可以实例化对象