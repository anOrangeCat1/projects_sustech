#include <iostream>
using namespace std;
#include <deque>

// deque容器的数据存取
void test1()
{
    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.push_front(100);
    d.push_front(200);
    d.push_front(300);

    //通过[]方式访问元素
    for (int i = 0; i < d.size(); i++)
    {
        cout << d[i] << " ";
    }
    cout << endl;

    //通过at方式访问元素
    for (int i = 0; i < d.size(); i++)
    {
        cout << d.at(i) << " ";
    }
    cout << endl;

    cout << "the first element: " << d.front() << endl;
    cout << "the last element: " << d.back() << endl;
}

int main()
{
    test1();

    return 0;
}