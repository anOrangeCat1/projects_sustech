#include <iostream>
using namespace std;

//打印数据函数
void showValue(const int &val)
{
    // val = 1000; 不允许修改
    cout << "val = " << val << endl;
}

int main()
{
    //常量引用
    //使用场景：主要用来修饰形参，防止误操作

    int a = 10;
    int &ref1 = a;        // wrong: int &ref = 10; 引用必须引一块合法的内存空间
    const int &ref2 = 10; //加上const之后 编译器将代码修改 int temp =10 ; const int &ref2 =temp;
                          //找不到内存的原名，只知道别名 ref2

    int b = 100;
    showValue(b);

    cout << "b = " << b << endl;

    return 0;
}