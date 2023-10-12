#include <iostream>
using namespace std;
#include <vector>

void printVector(vector<int> &v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

// vector容器的容量和大小

void test1()
{
    vector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    printVector(v1);

    if (v1.empty()) //如果为真 代表容器为空
    {
        cout << "v1 is empty" << endl;
    }
    else
    {
        cout << "v1 is not empty" << endl;
        cout << "capacity of v1: " << v1.capacity() << endl;
        cout << "size of v1: " << v1.size() << endl;
        // capacity >= size
    }

    //重新指定大小
    v1.resize(18, 100);
    printVector(v1); //如果重新指定比原来长 默认用0填充新的位置
    cout << "capacity of v1: " << v1.capacity() << endl;
    cout << "size of v1: " << v1.size() << endl;
    cout << endl;

    v1.resize(5);
    printVector(v1); //如果重新制定比原来短　超出部分会删除掉
    cout << "capacity of v1: " << v1.capacity() << endl;
    cout << "size of v1: " << v1.size() << endl;
    cout << endl;

    v1.resize(7);
    printVector(v1);
    cout << "capacity of v1: " << v1.capacity() << endl;
    cout << "size of v1: " << v1.size() << endl;
    cout << endl;
}

int main()
{
    test1();

    return 0;
}

//总结
/*
判断是否为空 -- empty
返回元素个数 -- size
返回容器容量 -- capacity
重新指定大小 -- resize
*/