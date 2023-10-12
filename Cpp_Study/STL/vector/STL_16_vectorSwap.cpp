#include <iostream>
using namespace std;
#include <vector>

// vector容器的互换

void printVector(vector<int> &v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

// 1.基本使用
void test1()
{
    cout << "Before Swap:" << endl;

    vector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    printVector(v1);

    vector<int> v2;
    for (int i = 10; i > 2; i--)
    {
        v2.push_back(i);
    }
    printVector(v2);

    cout << "After Swap:" << endl;
    v1.swap(v2);
    printVector(v1);
    printVector(v2);
}

// 2.实际用途
// 巧用swap可以收缩内存空间
void test2()
{
    vector<int> v;
    for (int i = 0; i < 100000; i++)
    {
        v.push_back(i);
    }

    cout << "capacity of v: " << v.capacity() << endl;
    cout << "size of v: " << v.size() << endl;

    //重新指定大小
    v.resize(3);
    cout << "capacity of v: " << v.capacity() << endl;
    cout << "size of v: " << v.size() << endl;

    //巧用swap收缩内存
    vector<int>(v).swap(v);
    cout << "capacity of v: " << v.capacity() << endl;
    cout << "size of v: " << v.size() << endl;

    // vector<int>(v) 匿名对象
}

int main()
{
    test1();
    test2();

    return 0;
}