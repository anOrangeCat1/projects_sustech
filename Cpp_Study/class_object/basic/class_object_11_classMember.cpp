#include <iostream>
using namespace std;
#include <string>

//类对象作为类成员

class Phone
{
public:
    string m_PName; //手机品牌名称

    Phone(string pName)
    {
        cout << "constructor of Phone" << endl;
        m_PName = pName;
    }

    ~Phone()
    {
        cout << "destructor of Phone" << endl;
    }
};

class Person
{
public:
    //姓名
    string m_Name;
    //手机
    Phone m_Phone;

    // Phone m_Phone = pName; 隐式转换法
    Person(string name, string pName) : m_Name(name), m_Phone(pName)
    {
        cout << "constructor of Person" << endl;
    }

    ~Person()
    {
        cout << "destructor of Person" << endl;
    }
};

void test1()
{
    Person p("Mike", "IPhone");

    cout << p.m_Name << " has " << p.m_Phone.m_PName << endl;
}

int main()
{
    test1();

    return 0;
}

//总结
//当其他类对象作为本类成员 构造时先构造成员类对象 再构造自身
//析构的顺序与构造相反