#include <iostream>
using namespace std;

//引用可以作为函数的返回值
// 1.不要返回局部变量的引用

int &test1() // wrong
{
    int a = 10; //局部变量存放在四区的 栈区
    return a;
}

// 2、函数的调用可以作为左值

int &test2()
{
    static int a = 10; //静态变量存放在 全局区  全局区上的数据在程序结束后系统释放
    return a;
}

int main()
{
    // int &ref1 = test1();

    // cout << ref1 << endl; //第一次结果正确，是因为编译器做了保留
    // cout << ref1 << endl; //第二次结果错误，因为a的内存已经释放

    int &ref2 = test2();
    cout << ref2 << endl;

    test2() = 1000; //如果函数的返回值是引用，这个函数调用可以作为左值
    cout << ref2 << endl;

    return 0;
}