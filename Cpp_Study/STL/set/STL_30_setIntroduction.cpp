#include <iostream>
using namespace std;
#include <set>

//所有元素都会在插入时自动被排序

// set/multiset 属于关联式容器 底层结构使用二叉树实现

// set 和 multiset 区别:
// set不允许容器有重复的元素 multiset允许容器有重复的元素

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

    //插入数据 只有 insert 方式
    s1.insert(10);
    s1.insert(40);
    s1.insert(30);
    s1.insert(20);
    s1.insert(30);

    //遍历容器
    printSet(s1);

    //拷贝构造
    set<int> s2(s1);
    printSet(s2);

    //赋值
    set<int> s3;
    s3 = s2;
    printSet(s3);
}

int main()
{
    test1();

    return 0;
}