#include <iostream>
using namespace std;

int main()
{
    // 32位操作系统下：指针占用4个字节空间
    // 64位操作系统下：指针占用8个字节空间
    // 不论是什么数据类型

    int a = 10;
    int *p = &a;

    cout << "size of (int *) = " << sizeof(int *) << endl;
    cout << "size of (float *) = " << sizeof(float *) << endl;
    cout << "size of (double *) = " << sizeof(double *) << endl;
    cout << "size of (char *) = " << sizeof(char *) << endl;

    return 0;
}