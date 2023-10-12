#include <iostream>
using namespace std;
#include <deque>
#include <algorithm> //标准算法头文件
#include <vector>

// deque容器排序

void printDeque(const deque<int> &d)
{
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void printVector(const vector<int> &v)
{
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test1()
{
    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.push_front(100);
    d.push_front(200);
    d.push_front(300);

    // 300 200 100 10 20 30
    printDeque(d);

    //排序 默认排序规则是 从小到大 升序
    //对于支持随机访问的迭代器的容器 都可以利用sort算法直接对其进行排序
    sort(d.begin(), d.end());
    printDeque(d);

    vector<int> v;
    v.push_back(3);
    v.push_back(2);
    v.push_back(4);
    v.push_back(1);
    printVector(v);

    sort(v.begin(), v.end());
    printVector(v);
}

int main()
{
    test1();

    return 0;
}