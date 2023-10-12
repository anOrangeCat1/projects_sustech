#include <iostream>
using namespace std;
#include <set>

// set容器 和 multiset容器的区别
void test1()
{
    set<int> s1;

    pair<set<int>::iterator, bool> ret = s1.insert(10);

    if (ret.second)
    {
        cout << "insert succeed" << endl;
    }
    else
    {
        cout << "insert fail" << endl;
    }

    ret = s1.insert(10);
    if (ret.second)
    {
        cout << "insert succeed" << endl;
    }
    else
    {
        cout << "insert fail" << endl;
    }

    multiset<int> ms;
    //允许插入重复值
    ms.insert(10);
    ms.insert(10);
    ms.insert(10);
    ms.insert(10);

    for (multiset<int>::iterator it = ms.begin(); it != ms.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

int main()
{
    test1();

    return 0;
}
//总结
//如果不允许插入重复数据可以利用set
//如果需要插入重复数据利用multiset