#include <iostream>
using namespace std;

int main()
{
    //注意事项
    // 1.引用必须初始化
    int a = 10;
    // int &b;//错误

    // 2.引用初始化后不能更改
    int &b = a;
    int c = 20;
    b = c; //赋值操作，而不是更改引用   不是说b变成了c的别名 而是改变b的值

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    return 0;
}