#include <iostream>
using namespace std;

int main()
{
    //引用：给变量起别名
    //语法：数据类型 &别名 = 原名

    int a = 10;
    int &b = a;//b和a公用同一块内存
    b = 20;
    cout << a;

    return 0;
}