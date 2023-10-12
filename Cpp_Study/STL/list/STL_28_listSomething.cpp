#include <iostream>
using namespace std;
#include <list>

//大小总结
/*
判断是否为空 -- empty
返回元素个数 -- size
重新指定个数 -- resize
*/

//插入删除总结
/*
尾插 -- push_back
尾删 -- pop_back
头插 -- push_front
头删 -- pop_front
插入 -- insert
删除 -- erase
移除 -- remove
清空 -- clear
*/

//数据存取总结
/*
list容器不可以通过[]或者at方式访问数据
迭代器是双向迭代器 不支持随机访问
可以: it++; it--;
不可以: it = it + 1; 不可以跳跃访问 即使是+1
返回第一个元素 -- front
返回最后一个元素 -- back
*/

//反转排序

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
    list<int> l1;

    l1.push_back(20);
    l1.push_back(10);
    l1.push_back(50);
    l1.push_back(40);
    l1.push_back(30);

    cout << "before reverse: " << endl;
    printList(l1);

    //反转
    cout << "after reverse: " << endl;
    l1.reverse();
    printList(l1);
}

bool myCompare(int v1, int v2)
{
    //降序 就让第一个数大于第二个数
    return v1 > v2;
}

//排序
void test2()
{
    list<int> l1;

    l1.push_back(20);
    l1.push_back(10);
    l1.push_back(50);
    l1.push_back(40);
    l1.push_back(30);

    cout << "before sort: " << endl;
    printList(l1);

    //反转
    cout << "after sort: " << endl;

    //所有不支持随机访问迭代器的容器 不可以用标准算法
    //不支持随机访问迭代器的容器 内部会提供对应一些算法
    // sort(l1.begin(),l1.end());错误

    l1.sort(); //默认排序规则 从小到大 升序
    printList(l1);

    l1.sort(myCompare);
    printList(l1);
}

int main()
{
    test1();
    test2();

    return 0;
}

//反转排序总结
/*
反转 -- reverse
排序 -- sort(成员函数)
*/