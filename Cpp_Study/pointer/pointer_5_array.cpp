#include <iostream>
using namespace std;

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "by array: arr[0] = " << arr[0] << endl;

    int *p = arr; // arr就是数组首地址

    cout << "by pointer: *p = " << *p << endl;

    cout << "size of int = " << sizeof(int) << endl; // int 大小为4个字节

    cout << "by pointer: p[1] = " << p[1] << endl;

    p++; //让指针向后偏移4个字节

    cout << "after p++" << endl;

    cout << "by pointer: *p = " << *p << endl;

    return 0;
}