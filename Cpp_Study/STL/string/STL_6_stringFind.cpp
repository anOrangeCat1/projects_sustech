#include <iostream>
using namespace std;

//字符串查找和替换

// 1.查找
void test1()
{
    string str1 = "abcdefgde";

    int pos = str1.find("de");

    if (pos == -1)
    {
        cout << "can not find " << endl;
    }
    else
    {
        cout << "pos = " << pos << endl;
    }

    // rfind
    // rfind 和 find 区别
    // rfind 从右往左查找 find从左往右查找
    pos = str1.rfind("de");

    cout << "pos = " << pos << endl;
}

// 2.替换
void test2()
{
    string str1 = "abcdef";

    //从 1号位置起 3个字符 替换成"1111"
    str1.replace(1, 3, "1111");
    cout << "str1 = " << str1 << endl;
}

int main()
{
    test1();
    test2();

    return 0;
}
