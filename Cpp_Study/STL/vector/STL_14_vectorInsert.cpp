#include <iostream>
using namespace std;
#include <vector>

// vector插入和删除
/*
push_back(ele);                                   //尾插ele元素
pop_back();                                       //尾删
insert(const_iterator pos, ele);                  //在pos位置插入ele元素
insert(const_iterator pos, int count, ele);       //在pos位置插入count个ele元素
erase(const_iterator pos);                        //删除pos位置元素
erase(const_iterator start, const_itrtator end);  //删除从start位置到end位置间的元素(包括end位置的元素)
clear();
*/

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
    vector<int> v1;
    //尾插
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    //遍历
    printVector(v1);

    //尾删
    v1.pop_back();
    printVector(v1);

    //插入 第一个参数是迭代器
    v1.insert(v1.begin(), 100);
    printVector(v1);

    v1.insert(v1.begin(), 2, 1000);
    printVector(v1);

    //删除
    v1.erase(v1.begin());
    printVector(v1);

    //区间删除
    v1.erase(v1.begin(), v1.begin() + 2);
    printVector(v1);

    //清空
    v1.clear();
    printVector(v1);
}

int main()
{
    test1();

    return 0;
}

//总结
/*
尾插 -- push_back
尾删 -- pop_back
插入 -- insert (位置迭代器)
删除 -- erase  (位置迭代器)
清空 -- clear
*/