// 软件界希望建立一种可重复利用的东西
// C++的面向对象和泛型编程的思想 目的就是复用性的提升
// 大多数情况下 数据结构和算法都未能有一套标准 导致被迫从事大量重复工作
// 为了建立数据结构和算法的一套标准 诞生了STL

// STL基本概念
/*
STL(Standard Template Library) 标准模板库
STL从广义上分为: 容器(container) 算法(algorithm) 迭代器(iterator)
容器和算法之间通过迭代器进行无缝衔接
STL几乎所有的代码都采用了模板类或者模板函数
*/

// STL 六大组件
//容器 算法 迭代器 仿函数 适配器(配接器) 空间配置器
/*
1.容器: 各种数据结构 如 vector, list, deque, set, map等 用来存放数据
2.算法: 各种常用的算法 如 sort, find, copy, for_each等
3.迭代器: 扮演了容器和算法之间的胶合剂
4.仿函数：行为类似函数 可作为算法的容器 重载的小括号()
5.适配器: 一种用来修饰容器或者仿函数或迭代器接口的东西
6.空间配置器: 负责空间的配置和管理
*/

//容器
/*
常用数据结构: 数组 链表 树 栈 队列 集合 映射表
分为两种:
序列式容器: 强调值的排序 序列式容器中的每个元素均有固定位置
关联式容器: 二叉树结构 各个元素之间没有严格的物理上的顺序关系
*/

//算法
/*
算法分为: 质变算法 和 非质变算法
质变算法: 是指运算过程中会更改区间内元素的内容 例如 拷贝 替换 删除 等
非质变算法: 是指运算过程中不会更改区间内元素的内容 例如 查找 计数 遍历 寻找极值 等
*/

//迭代器
/*
提供一种方法 使之能够依序寻访某个容器所含的各个元素 而又无需暴露该容器的内部表示方式
每个容器都有自己的专属迭代器
迭代器使用非常类似于指针 初学阶段可以先理解迭代器为指针
常用的容器中迭代器种类为 双向迭代器 和 随机访问迭代器
*/

// Example
// vector 可以理解为数组
/*
容器: vector
算法: for_each
迭代器: vector<int>::iterator
*/

#include <iostream>
using namespace std;
#include <vector>
#include <algorithm> //标准算法的头文件

void myPrint(int val)
{
    cout << val << endl;
}

// vector容器存放内置数据类型
void test1()
{
    //创建了一个vector容器 数组
    vector<int> v;
    //向容器中插入数据
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    //通过迭代器访问容器中数据
    vector<int>::iterator itBegin = v.begin(); //起始迭代器 指向容器中第一个元素
    vector<int>::iterator itEnd = v.end();     //结束迭代器 指向容器中最后一个元素的下一个位置

    //第一种遍历方式
    while (itBegin != itEnd)
    {
        cout << *itBegin << endl;
        itBegin++;
    }

    //第二种遍历方式
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << endl;
    }

    //第三种遍历方式 利用STL中遍历算法
    for_each(v.begin(), v.end(), myPrint);
}

int main()
{
    test1();

    return 0;
}