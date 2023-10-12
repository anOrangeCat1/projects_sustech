#include <iostream>
using namespace std;

//函数调用运算符重载

//打印输出类
class MyPrint
{
public:
    //重载函数调用运算符
    void operator()(string test)
    {
        cout << test << endl;
    }
};

void MyPrint2(string test)
{
    cout << test << endl;
}

void test1()
{
    MyPrint myPrint;

    myPrint("Hello World!"); //由于使用起来非常类似于函数调用 因此称为仿函数

    MyPrint2("Hello World!");
}

//仿函数非常灵活 没有固定写法
class MyAdd
{
public:
    int operator()(int num1, int num2)
    {
        return num1 + num2;
    }
};

void test2()
{
    MyAdd myAdd;
    int result = myAdd(100, 200);
    cout << "result = " << result << endl;

    //匿名函数对象
    cout << "MyAdd()(100,100) = " << MyAdd()(100, 100) << endl;
}

int main()
{
    test1();
    test2();

    return 0;
}