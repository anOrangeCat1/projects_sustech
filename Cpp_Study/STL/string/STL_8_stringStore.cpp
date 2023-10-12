#include <iostream>
using namespace std;

// string中单个字符存取方式有两种
// char& operator[](int n);  // 通过[]方式取字符
// char& at(int n);          // 通过at方法取字符

void test1()
{
    string str = "hello";

    cout << "str = " << str << endl;

    // 1.通过 [] 访问单个字符
    for (int i = 0; i < str.size(); i++)
    {
        cout << str[i] << " ";
    }
    cout << endl;

    // 2.通过 at 方式访问单个字符
    for (int i = 0; i < str.size(); i++)
    {
        cout << str.at(i) << " ";
    }
    cout << endl;

    //修改单个字符
    str[0] = 'X';
    cout << "str = " << str << endl;

    str.at(1) = 'x';
    cout << "str = " << str << endl;
}

int main()
{
    test1();

    return 0;
}