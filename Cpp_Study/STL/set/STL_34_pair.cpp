#include <iostream>
using namespace std;
#include <string>

// pair对组创建
void test1()
{
    //第一种方式
    pair<string, int> p1("Tom", 20);

    cout << "Name: " << p1.first << "  Age: " << p1.second << endl;

    //第二种方式
    pair<string, int> p2 = make_pair("Jerry", 30);

    cout << "Name: " << p2.first << "  Age: " << p2.second << endl;
}

int main()
{
    test1();

    return 0;
}