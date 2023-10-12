#include <iostream>
using namespace std;
#include <list>

//链表
//结点 数据域 和 指针域
//优点: 可以对任意位置进行快速插入或删除元素 采用动态存储分配 不会造成内存浪费和溢出
//缺点: 容器遍历速度没有数组快 占用空间比数组大

// STL中的链表是一个双向循环链表
//由于链表的储存方式并不是连续的内存空间 因此链表list中的迭代器只支持前移和后移 属于双向迭代器

// list重要性质 插入和删除操作都不会造成原有list迭代器失效 这在vector是不成立的

// STL中list和vector是两个最常被使用的容器 各有优缺点

// list容器构造函数

void printList(const list<int> &l)
{
    for (list<int>::const_iterator it = l.begin(); it != l.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test1()
{
    //创建list容器
    list<int> l1;

    //添加数据
    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);
    l1.push_back(40);

    //遍历容器
    printList(l1);

    //区间方式构造
    list<int> l2(l1.begin(), l1.end());
    printList(l2);

    //拷贝构造
    list<int> l3(l2);
    printList(l3);

    // n个element
    list<int> l4(10, 1000);
    printList(l4);
}

int main()
{
    test1();

    return 0;
}