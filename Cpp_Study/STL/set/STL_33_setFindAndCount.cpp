#include <iostream>
using namespace std;
#include <set>

// set容器的查找和统计

//查找
void test1()
{
    set<int> s1;

    //插入数据
    s1.insert(10);
    s1.insert(30);
    s1.insert(40);
    s1.insert(20);

    set<int>::iterator pos = s1.find(30);

    if (pos != s1.end())
    {
        cout << "find the element " << *pos << endl;
    }
    else
    {
        cout << "not find " << endl;
    }
}

//统计
void test2()
{
    set<int> s1;

    //插入数据
    s1.insert(10);
    s1.insert(30);
    s1.insert(40);
    s1.insert(20);
    s1.insert(30);
    s1.insert(30);
    //对于set而言 统计的结果 要么是0 要么是1

    //统计30的个数
    int num = s1.count(30);
    cout << "num = " << num << endl;
}

int main()
{
    test1();
    test2();

    return 0;
}

//总结
/*
查找 -- find(返回的是迭代器)
统计 -- count(对于涩图 结果为0或1)
*/