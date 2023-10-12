#include <iostream>
using namespace std;

int *func()
{
    //利用 new 关键字 可以将数据开辟到堆区

    //指针本质也是局部变量 放在栈上 指针保存的数据放在堆区
    int *p = new int(10);
    return p;
}

int main()
{
    //堆区 由程序员分配释放 若程序员不释放 程序结束时由操作系统回收
    //在C++中主要利用 new 在堆区开辟内存

    int *p = func();

    cout << *p << endl;
    cout << *p << endl;

    return 0;
}