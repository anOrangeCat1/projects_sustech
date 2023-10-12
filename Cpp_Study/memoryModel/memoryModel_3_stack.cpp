#include <iostream>
using namespace std;

int *func()
{
    int a = 10; //局部变量
    return &a;  //返回局部变量的地址

    //局部变量存放在栈区，栈区的数据在函数执行完后自动释放
}

int main()
{
    //栈区 由编译器自动分配释放
    //存放函数的参数值 局部变量等
    //注意事项：不要返回局部变量地址

    //接收func函数的返回值
    int *p = func();

    cout << *p << endl; //第一次可以打印正确的数字 因为编译器做了保留
    cout << *p << endl; //第二次这个数据不再保留

    //形参数据也会放在栈区

    return 0;
}