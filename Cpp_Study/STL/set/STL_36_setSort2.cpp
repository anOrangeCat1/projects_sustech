#include <iostream>
using namespace std;
#include <set>

// set容器排序 存放自定义数据类型

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

class comparePerson
{
public:
    bool operator()(const Person &p1, const Person &p2)
    {
        //按照年龄降序
        return p1.m_Age > p2.m_Age;
    }
};

void test1()
{
    //自定义的数据类型 都会指定排序规则
    set<Person, comparePerson> s;

    Person p1("aaa", 35);
    Person p2("bbb", 45);
    Person p3("ccc", 40);
    Person p4("ddd", 25);

    s.insert(p1);
    s.insert(p2);
    s.insert(p3);
    s.insert(p4);

    for (set<Person, comparePerson>::iterator it = s.begin(); it != s.end(); it++)
    {
        cout << "Name: " << it->m_Name << "  Age: " << it->m_Age << endl;
    }
    cout << endl;
}

int main()
{
    test1();

    return 0;
}