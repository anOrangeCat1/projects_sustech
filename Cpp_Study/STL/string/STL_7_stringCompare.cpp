#include <iostream>
using namespace std;

//字符串之间比较
//根据ASCII码进行对比
// = 返回 0
// > 返回 1
// < 返回 -1

void test1()
{
    string str1 = "Hello";
    string str2 = "hello";

    if (str1.compare(str2) == 0)
    {
        cout << "str1 = str2" << endl;
    }
    else if (str1.compare(str2) > 0)
    {
        cout << "str1 > str2" << endl;
    }
    else
    {
        cout << "str1 < str2" << endl;
    }
}

int main()
{
    test1();

    return 0;
}

//比较主要用于判断是否相等 比较大小意义不大