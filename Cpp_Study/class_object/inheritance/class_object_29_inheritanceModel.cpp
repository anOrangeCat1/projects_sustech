#include <iostream>
using namespace std;

//继承中的对象模型

class Base
{
public:
    int m_A;

protected:
    int m_B;

private:
    int m_C;
};

//公共继承
class Son : public Base
{
public:
    int m_D;
};

void test1()
{
    // 16 byte
    //父类中所有非静态成员属性都会被子类继承下去
    //父类中私有成员属性 是被编译器隐藏了 因此是访问不到 但是确实被继承下去了
    cout << "size of Son = " << sizeof(Son) << endl;
}

int main()
{
    test1();

    return 0;
}