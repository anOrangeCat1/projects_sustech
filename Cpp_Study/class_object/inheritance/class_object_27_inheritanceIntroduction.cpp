#include <iostream>
using namespace std;

// //普通实现页面

// // Java页面
// class Java
// {
// public:
//     void header()
//     {
//         cout << "header" << endl;
//     }

//     void footer()
//     {
//         cout << "footer" << endl;
//     }

//     void left()
//     {
//         cout << "Java, Python, C++ ..." << endl;
//     }

//     void content()
//     {
//         cout << "videos of Java" << endl;
//     }
// };

// // Python页面
// class Python
// {
// public:
//     void header()
//     {
//         cout << "header" << endl;
//     }

//     void footer()
//     {
//         cout << "footer" << endl;
//     }

//     void left()
//     {
//         cout << "Java, Python, C++ ..." << endl;
//     }

//     void content()
//     {
//         cout << "videos of Python" << endl;
//     }
// };

// // C++页面
// class Cpp
// {
// public:
//     void header()
//     {
//         cout << "header" << endl;
//     }

//     void footer()
//     {
//         cout << "footer" << endl;
//     }

//     void left()
//     {
//         cout << "Java, Python, C++ ..." << endl;
//     }

//     void content()
//     {
//         cout << "videos of C++" << endl;
//     }
// };

// void test1()
// {
//     cout << "Java page" << endl;
//     Java ja;
//     ja.header();
//     ja.footer();
//     ja.left();
//     ja.content();

//     cout << "--------------" << endl;
//     cout << "Python page" << endl;
//     Python py;
//     py.header();
//     py.footer();
//     py.left();
//     py.content();

//     cout << "--------------" << endl;
//     cout << "C++ page" << endl;
//     Python cpp;
//     cpp.header();
//     cpp.footer();
//     cpp.left();
//     cpp.content();
// }

// 继承实现页面

// 公共页面类
class BasePage
{
public:
    void header()
    {
        cout << "header" << endl;
    }

    void footer()
    {
        cout << "footer" << endl;
    }

    void left()
    {
        cout << "Java, Python, C++ ..." << endl;
    }
};

//继承的好处: 减少重复代码
//语法: class 子类 : 继承方式 父类
//子类 也称为派生类
//父类 也称为基类
//派生类中的成员 包含两大部分
//一类是从基类继承过来的 一类是自己增加的成员
//从基类继承过来的表现其共性 而新增的成员体现了其个性

// Java页面
class Java : public BasePage
{
public:
    void content()
    {
        cout << "videos of Java" << endl;
    }
};

// Python页面
class Python : public BasePage
{
public:
    void content()
    {
        cout << "videos of Phthon" << endl;
    }
};

// C++页面
class Cpp : public BasePage
{
public:
    void content()
    {
        cout << "videos of Cpp" << endl;
    }
};

void test1()
{
    cout << "Java page" << endl;
    Java ja;
    ja.header();
    ja.footer();
    ja.left();
    ja.content();

    cout << "--------------" << endl;
    cout << "Python page" << endl;
    Python py;
    py.header();
    py.footer();
    py.left();
    py.content();

    cout << "--------------" << endl;
    cout << "C++ page" << endl;
    Cpp cpp;
    cpp.header();
    cpp.footer();
    cpp.left();
    cpp.content();
}

int main()
{
    test1();

    return 0;
}