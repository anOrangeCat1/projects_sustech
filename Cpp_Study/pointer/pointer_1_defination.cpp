//指针来保存一个地址

#include <iostream>
using namespace std;

int main()
{
    int a = 10;
    int *p;
    p = &a;

    //指针前加 * 代表解引用，找到指针指向内存中的数据
    *p = 1000;
    cout << "a = " << a << endl;
    cout << "*P = " << *p << endl;
    
    return 0;
}