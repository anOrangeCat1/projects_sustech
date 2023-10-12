#include <iostream>
using namespace std;

//父类和子类的构造和析构顺序是谁先谁后？

//继承中的构造和析构顺序
class Base
{
public:
    Base()
    {
        cout << "constructor of Base" << endl;
    }

    ~Base()
    {
        cout << "deconstructor of Base" << endl;
    }
};

class Son : public Base
{
public:
    Son()
    {
        cout << "constructor of Son" << endl;
    }

    ~Son()
    {
        cout << "deconstructor of Son" << endl;
    }
};

void test1()
{
    Son s;
    //继承中的构造和析构如下:
    //先构造父类 再构造子类 析构的顺序与构造的顺序相反
}

int main()
{
    test1();

    return 0;
}