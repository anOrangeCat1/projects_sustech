#include <iostream>
using namespace std;
#include <deque>

// deque容器大小操作

void printDeque(const deque<int> &d)
{
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test1()
{
    deque<int> d1;
    for (int i = 0; i < 10; i++)
    {
        d1.push_back(i);
    }
    printDeque(d1);

    if (d1.empty())
    {
        cout << "d1 is empty" << endl;
    }
    else
    {
        cout << "d1 is not empty" << endl;
        cout << "size of d1: " << d1.size() << endl;
        // deque容器没有容量的概念
    }

    //重新指定大小
    d1.resize(15);
    printDeque(d1);

    d1.resize(20, 1);
    printDeque(d1);

    d1.resize(5);
    printDeque(d1);
}

int main()
{
    test1();

    return 0;
}

//deque没有容量(capacity)的概念
/*
判断是否为空 -- empty
返回元素个数 -- size
重新指定个数 -- resize
*/