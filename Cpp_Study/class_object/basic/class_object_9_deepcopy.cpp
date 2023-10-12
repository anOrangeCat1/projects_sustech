#include <iostream>
using namespace std;

//深拷贝和浅拷贝

//浅拷贝 简单的赋值拷贝操作
//深拷贝 在堆区重新申请空间 进行拷贝工作 

//浅拷贝带来的问题 堆区的内存的重复释放
//解决 深拷贝

//总结 如果属性有在堆区 new和指针 开辟的 一定要自己提供拷贝构造函数 防止浅拷贝带来的问题

class Person
{
public:
    int age;
    int *height;

    Person()
    {
        cout << "default constructor" << endl;
    }

    Person(int a, int h)
    {
        age = a;
        height = new int(h);
        cout << "parameter constructor" << endl;
    }

    //自己实现拷贝构造函数 解决浅拷贝带来的问题
    Person(const Person &p)
    {
        age = p.age;
        // height = p.height; // 编译器默认实现就是这行代码 浅拷贝
        height = new int(*p.height); //深拷贝
        cout << "copy constructor" << endl;
    }

    ~Person()
    {
        //析构代码 将堆区开辟数据做释放
        if (height != NULL)
        {
            delete height;
            height = NULL;
        }
        cout << "destructor" << endl;
    }
};

void test1()

{
    Person p1(18, 160);
    cout << "age of p1: " << p1.age << endl;
    cout << "height of p1: " << *p1.height << endl;

    Person p2(p1);
    cout << "age of p2: " << p2.age << endl;
    cout << "height of p2: " << *p2.height << endl;
}

int main()
{
    test1();

    return 0;
}