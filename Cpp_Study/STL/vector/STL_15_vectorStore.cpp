#include <iostream>
using namespace std;
#include <vector>

// vector容器 数据存取

void test1()
{
    vector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    //利用 中括号[] 方式访问数组元素
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;

    //利用成员函数 at 访问元素
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1.at(i) << " ";
    }
    cout << endl;

    //获取第一个元素
    cout << "the first element: " << v1.front() << endl;

    //获取最后一个元素
    cout << "the last element: " << v1.back() << endl;
}

int main()
{
    test1();

    return 0;
}
