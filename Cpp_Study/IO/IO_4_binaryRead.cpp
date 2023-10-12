#include <iostream>
using namespace std;
#include <fstream>

class Person
{
public:
    char m_Name[64];
    int m_Age;
};

//二进制文件 读文件
void test1()
{
    // 1.包含头文件

    // 2.创建流对象
    ifstream ifs;

    // 3.打开文件 判断文件是否打开成功
    ifs.open("person.txt", ios::in | ios::binary);
    if (!ifs.is_open())
    {
        cout << "fail to open!" << endl;
        return;
    }

    // 4.读文件
    Person p;

    ifs.read((char *)&p, sizeof(Person));

    cout << "Name: " << p.m_Name << endl;
    cout << "Age: " << p.m_Age << endl;

    // 5.关闭文件
    ifs.close();
}

int main()
{
    test1();

    return 0;
}