#include <iostream>
using namespace std;

// 1. 构造函数的分类和调用
//分类
//按照参数分类  无参构造（默认构造）和 有参构造
//按照类型分类  普通构造 和 拷贝构造
class Person
{
private:
    int Age;

public:
    //构造函数
    Person()
    {
        cout << "default constructor of Person." << endl;
    }

    Person(int a)
    {
        Age = a;
        cout << "parameter constructor of Person." << endl;
    }

    //拷贝构造函数
    Person(const Person &p)
    {
        //将传入的人身上的所有属性 拷贝到自己身上
        Age = p.Age;
        cout << "copy constructor of Person." << endl;
    }

    ~Person()
    {
        cout << "destructor of Person." << endl;
    }
};

//调用
void test1()
{
    // 1. 括号法
    Person p1;     //调用 默认构造函数
    Person p2(10); //调用 有参构造函数
    Person p3(p2); //调用 拷贝构造函数

    //注意事项
    //调用默认构造函数的时候 不要加()
    //即不要 Person p1();
    //因为编译器会认为是一个函数的声明 不会认为在创建对象

    // 2. 显示法
    Person p4;
    Person p5 = Person(10); //调用 有参构造
    Person p6 = Person(p5); //调用 拷贝构造

    //等号右侧 Person(10); 匿名对象 特点：当前行执行结束后 系统会立即回收匿名对象
    Person(10);
    cout << "aaaaa" << endl;

    //注意事项2
    //不要利用拷贝构造函数 初始化匿名对象
    //即 Person(p2);
    //编译器会认为 Person(p2) == Person p2 对象声明 造成重定义

    // 3. 隐式转换法
    Person p7 = 10; //相当于 写了 Person p7 = Person(10);
    Person p8 = p2; //拷贝构造
}

int main()
{
    test1();

    return 0;
}