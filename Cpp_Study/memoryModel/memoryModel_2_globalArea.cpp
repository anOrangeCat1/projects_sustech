#include <iostream>
using namespace std;

//全局变量
int g_a = 10;
int g_b = 10;

// const修饰的全局变量 全局常量
const int c_g_a = 10;
const int c_g_b = 10;

int main()
{
    //全局区
    //全局变量、静态变量、常量

    //创建普通局部变量

    int a = 10;
    int b = 10;

    cout << "address of a: " << (long long)&a << endl;
    cout << "address of b: " << (long long)&b << endl;
    cout << "address of g_a: " << (long long)&g_a << endl;
    cout << "address of g_b: " << (long long)&g_b << endl;

    //静态变量 在普通变量前加 static 就是静态变量
    static int s_a = 10;
    static int s_b = 10;

    cout << "address of s_a: " << (long long)&s_a << endl;
    cout << "address of s_b: " << (long long)&s_b << endl;

    //常量
    //字符串常量
    cout << "address of string: " << (long long)&"Hello World" << endl;

    // const修饰变量
    // const修饰的全局变量 const修饰的局部变量

    cout << "address of c_g_a: " << (long long)&c_g_a << endl;
    cout << "address of c_g_b: " << (long long)&c_g_b << endl;

    const int c_l_a = 10; // c = const; g = global; l = local
    const int c_l_b = 10;

    cout << "address of c_l_a: " << (long long)&c_l_a << endl;
    cout << "address of c_l_b: " << (long long)&c_l_b << endl;

    //全局区存放 全局变量 静态变量 常量
    //常量区存放 const修饰的全局常量 字符串常量

    return 0;
}