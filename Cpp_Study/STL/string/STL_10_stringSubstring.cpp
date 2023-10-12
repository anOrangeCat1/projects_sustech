#include <iostream>
using namespace std;

// string字串

void test1()
{
    string str = "abcdef";
    string subStr = str.substr(1, 3);

    cout << "subStr = " << subStr << endl;
}

//实用操作
void test2()
{
    string email = "zhangsan@sina.com";

    //从邮件地址中获取 用户名信息
    int pos = email.find("@"); // 8
    cout << "pos = " << pos << endl;

    string userName = email.substr(0, pos);
    cout << "userName = " << userName;
}

int main()
{
    test1();
    test2();

    return 0;
}