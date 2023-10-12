#include <iostream>
using namespace std;

void func(int &ref)
{
    ref = 100; // ref是引用，转换为*ref = 100;
}

int main()
{
    //引用的本质在C++内部实现是一个指针常量

    int a = 10;

    //自动转换为 int* const ref = &a;
    //指针常量是指针指向不能改，也说明为什么引用不可更改
    int &ref = a;
    ref = 20; //内部发现ref是引用，自动帮我们转换为：*ref = 20;

    cout << "a = " << a << endl;
    cout << "ref = " << ref << endl;

    func(a);

    cout << "a = " << a << endl;
    cout << "ref = " << ref << endl;

    // C++推荐引用技术，因为语法方便，引用本质是指针常量，但是所有的指针操作编译器帮我们做了

    return 0;
}