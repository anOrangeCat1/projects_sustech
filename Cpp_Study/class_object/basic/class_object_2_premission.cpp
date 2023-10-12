#include <iostream>
#include <string.h>
using namespace std;

//访问权限
//公共权限 pubulic      成员 类内可以访问 类外也可以访问
//保护权限 protected    成员 类内可以访问 类外不可以访问 儿子可以访问父亲中的保护内容
//私有权限 private      成员 类内可以访问 类外不可以访问 儿子不可以访问父亲的私有内容

class Person
{
    //公共权限
public:
    string Name;

    //保护权限
protected:
    string Car;

    //私有权限
private:
    int Password;

public:
    void func()
    {
        Name = "Mike";
        Car = "Porsche";
        Password = 123456;
    }
};

int main()
{

    return 0;
}