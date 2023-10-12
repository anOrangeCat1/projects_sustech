#include <iostream>
using namespace std;
#include <queue>

// queue是一种 先进先出 的数据结构
// 一端只能进数据 另一端只能出数据
// 只有队头和队尾数据才能访问 因此queue也不能遍历

//队列 queue

class Person
{
public:
    string m_Name;
    int m_Age;

    Person(string name, int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
};

void test1()
{
    //创建队列
    queue<Person> q;

    //准备数据
    Person p1("aaa", 111);
    Person p2("bbb", 222);
    Person p3("ccc", 333);
    Person p4("ddd", 444);

    q.push(p1);
    q.push(p2);
    q.push(p3);
    q.push(p4);

    cout << "size of q: " << q.size() << endl;

    //判断只要队列不为空 查看队头 查看队尾 出队
    while (!q.empty())
    {
        //查看队头
        cout << "Top of q: Name: " << q.front().m_Name << "  Age: " << q.front().m_Age << endl;

        //查看队尾
        cout << "Back of q: Name: " << q.back().m_Name << "  Age: " << q.back().m_Age << endl;

        //出队
        q.pop();
    }

    cout << "size of q: " << q.size() << endl;
}

int main()
{
    test1();

    return 0;
}

//总结
/*
入队 -- push
出队 -- pop
返回队头元素 -- front
返回队尾元素 -- back
判断队是否为空 -- empty
返回队列大小 -- size
*/