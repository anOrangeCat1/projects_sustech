#include <iostream>
using namespace std;

// 1. new 的基本语法
int *func()
{
    //在堆区创建整形数据
    // new返回的是 该数据类型的指针
    int *p = new int(10);
    return p;
}

void test1()
{
    int *p = func();
    cout << *p << endl;
    //堆区的数据由程序员管理释放
    //如果像释放堆区数据 利用关键字 delete

    delete p;
    cout << *p << endl; //内存已经被释放
    cout << *p << endl;
}

// 2.在堆区利用 new 开辟数组
void test2()
{
    //在 堆区 创建10整型数据的 数组
    int *arr = new int[10]; //代表数组有10个元素

    for (int i = 0; i < 10; i++)
    {
        arr[i] = i + 100; //给10个元素赋值 100-109
    }

    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << endl;
    }

    //释放堆区数组
    //释放数组时要加[]
    delete[] arr;
}

int main()
{
    //在C++中利用 new 操作符在堆区开辟数据
    //手动释放内存 delete 操作符
    //利用new创建数据的数据，会返回数据对应的类型的指针

    test1();
    test2();

    return 0;
}