#include <iostream>
using namespace std;
#include <vector>
#include <string>

// vector容器中存放自定义数据类型
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
    vector<Person> v;

    Person p1("Aaa", 10);
    Person p2("Bbb", 20);
    Person p3("Ccc", 30);
    Person p4("Ddd", 40);
    Person p5("Eee", 50);

    //向容器中添加数据
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);

    //遍历容器中的数据
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        // cout << "Name: " << (*it).m_Name << "  Age: " << (*it).m_Age << endl;
        cout << "Name: " << it->m_Name << "  Age: " << it->m_Age << endl;
    }
}

//存放自定义数据类型的 指针
void test2()
{
    vector<Person *> v;

    Person p1("Aaa", 10);
    Person p2("Bbb", 20);
    Person p3("Ccc", 30);
    Person p4("Ddd", 40);
    Person p5("Eee", 50);

    //向容器中添加数据
    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    v.push_back(&p5);

    //遍历容器
    for (vector<Person *>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "Name: " << (*it)->m_Name << "  Age: " << (*it)->m_Age << endl;
    }
}

int main()
{
    test1();
    test2();

    return 0;
}