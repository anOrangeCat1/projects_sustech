#include <iostream>
using namespace std;
#include <map>

// map基本概念
/*
map中所有元素都是pair
pair中第一个元素为key(键值) 起到索引作用 第二个元素为value(实值)
所有元素都会根据元素的键值自动排序

本质
map/multimap 属于 关联式容器 底层结构是用二叉树实现

优点
可以根据key值快速找到value值 高效
map和multimap 允许/不允许 有重复的key值 value值可以重复
*/

// map容器 构造和赋值

void printMap(map<int, int> &m)
{
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "key = " << (*it).first << "  value = " << it->second << endl;
    }
}

void test1()
{
    //创建map容器
    map<int, int> m;

    m.insert(pair<int, int>(1, 10));
    m.insert(pair<int, int>(3, 30));
    m.insert(pair<int, int>(4, 40));
    m.insert(pair<int, int>(2, 20));

    printMap(m);

    //拷贝构造
    map<int, int> m2(m);
    printMap(m2);

    //赋值
    map<int, int> m3;
    m3 = m2;
    printMap(m3);
}

int main()
{
    test1();

    return 0;
}

//map容器大小和互换
//总结
/*
统计大小 -- size
判断是否为空 -- empty
交换容器 -- swap
*/