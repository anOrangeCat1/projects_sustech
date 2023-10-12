#include <iostream>
using namespace std;
#include <vector>

// vector数据结构和数组非常类似 也称为 单端数组
// vector与普通数组区别 vector可以 动态扩展
// 动态扩展机制: 并不是在原空间之后续借新空间 而是找更大的内存空间 然后将原数据拷贝到新空间 释放原来空间

// vector容器的迭代器是支持随机访问的迭代器

// vector的构造函数

void printVector(vector<int> &v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test1()
{
    //默认构造 无参构造
    vector<int> v1;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    printVector(v1);

    //通过区间方式进行构造 注意区间开闭 前闭后开 v1.end()不会取到
    vector<int> v2(v1.begin(), v1.end());
    printVector(v2);

    //用n个elem方式构造
    vector<int> v3(10, 100);
    printVector(v3);

    //拷贝构造
    vector<int> v4(v3);
    printVector(v4);
}

int main()
{
    test1();

    return 0;
}