#include <iostream>
#include <list>
using namespace std;
#include <string>

// list容器排序案例 对于自定义数据类型进行排序

// 按照年龄进行升序 如果年龄相同就按照身高进行降序

class Person
{
public:
    string m_Name;
    int m_Age;
    int m_Height;

    Person(string name, int age, int height)
    {
        this->m_Name = name;
        this->m_Age = age;
        this->m_Height = height;
    }
};

//指定排序规则
bool myCompare(Person &p1, Person &p2)
{
    if (p1.m_Age == p2.m_Age)
    {
        //年龄相同 按照身高降序
        return p1.m_Height > p2.m_Height;
    }
    
    //按照年龄升序
    return p1.m_Age < p2.m_Age;
}

void test1()
{
    list<Person> l; // 创建容器

    Person p1("aaa", 35, 175);
    Person p2("bbb", 45, 180);
    Person p3("ccc", 40, 170);
    Person p4("ddd", 25, 190);
    Person p5("eee", 35, 160);
    Person p6("fff", 35, 200);

    //插入数据
    l.push_back(p1);
    l.push_back(p2);
    l.push_back(p3);
    l.push_back(p4);
    l.push_back(p5);
    l.push_back(p6);

    cout << "before sort:" << endl;

    for (list<Person>::iterator it = l.begin(); it != l.end(); it++)
    {
        cout << "Name: " << (*it).m_Name << "  Age: " << it->m_Age << "  Height: " << it->m_Height;
        cout << endl;
    }

    //排序
    cout << "---------------------------" << endl;
    cout << "after sort: " << endl;
    l.sort(myCompare);
    for (list<Person>::iterator it = l.begin(); it != l.end(); it++)
    {
        cout << "Name: " << (*it).m_Name << "  Age: " << it->m_Age << "  Height: " << it->m_Height;
        cout << endl;
    }
}

int main()
{
    test1();

    return 0;
}