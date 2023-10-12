#include <iostream>
using namespace std;

int main()
{
    // const修饰指针——常量指针
    // 特点：指针的指向可以改，但是指针指向的值不可以改

    // const修饰常量——指针常量
    // 特点：指针的指向不可以改，但是指针指向的值可以改

    // const既修饰指针又修饰常量
    // 特点：指针的指向和指向的值都不可以改

    int a = 10;
    int b = 20;

    //常量指针
    const int *p1 = &a;
    //*p = 100; 错误
    p1 = &b; //正确

    //指针常量
    int *const p2 = &a;
    *p2 = 100; //正确
    // p2 = &b; 错误

    // const修饰指针和常量
    const int *const p3 = &a;
    //*p3 = 100; 错误
    // p3 = &b; 错误

    return 0;
}