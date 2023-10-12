#include <iostream>
using namespace std;

//对string字符串进行 插入和删除 字符操作

void test1()
{
    string str = "Hello";

    //插入
    str.insert(1, "111");
    cout << "str = " << str << endl;

    //删除
    str.erase(1, 3);
    cout << "str = " << str << endl;
}

int main()
{
    test1();

    return 0;
}