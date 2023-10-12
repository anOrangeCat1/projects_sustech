#include <iostream>
#include <string.h>
using namespace std;

//成员属性设置为私有
// 1.可以自己控制读写权限
// 2.对于写可以检测数据的有效性

//设计人类
class Person
{
private:
    //姓名 可读 可写
    string Name;
    //年龄 可读 可写 如果想修改 年龄范围必须是0—150之间
    int Age;
    //情人 只写
    string Lover;

public:
    void setName(string name)
    {
        Name = name;
    }

    string getName()
    {
        return Name;
    }

    void setAge(int age)
    {
        if (age < 0 || age > 150)
        {
            Age = 0;
            cout << "wrong age!" << endl;
            return;
        }
        Age = age;
    }

    int getAge()
    {
        // age = 0; //初始化
        return Age;
    }

    void setLover(string lover)
    {
        Lover = lover;
    }
};

int main()
{
    Person p;
    p.setName("Mike");
    p.setAge(18);
    p.setLover("Amy");

    cout << "Name: " << p.getName() << endl;
    cout << "Age: " << p.getAge() << endl;

    return 0;
}