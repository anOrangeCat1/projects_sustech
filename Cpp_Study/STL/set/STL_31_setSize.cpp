#include <iostream>
using namespace std;
#include <set>

// set容器 大小和交换

void printSet(set<int> s)
{
    for (set<int>::iterator it = s.begin(); it != s.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test1()
{
    set<int> s1;

    s1.insert(10);
    s1.insert(40);
    s1.insert(30);
    s1.insert(20);

    //遍历容器
    printSet(s1);

    //判断是否为空
    if (s1.empty())
    {
        cout << "s1 is empty" << endl;
    }
    else
    {
        cout << "s1 is not empty" << endl;
        cout << "size of s1: " << s1.size() << endl;
    }
}

//交换
void test2()
{
    set<int> s1;

    s1.insert(10);
    s1.insert(40);
    s1.insert(30);
    s1.insert(20);

    set<int> s2;

    s2.insert(100);
    s2.insert(400);
    s2.insert(300);
    s2.insert(200);

    printSet(s1);
    printSet(s2);

    s1.swap(s2);
    printSet(s1);
    printSet(s2);
}

int main()
{
    test1();
    test2();

    return 0;
}