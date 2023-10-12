#include <iostream>
using namespace std;

//圆周率
const double PI = 3.14;

//设计一个圆类 求圆的周长
class Circle
{
    //访问权限
    //公共权限
public:
    //属性
    int r;

    //行为
    //获取圆的周长
    double perimeter()
    {
        return 2 * PI * r;
    }
};

int main()
{
    // C++面向对象的三大特性：封装 继承 多态
    //具有相同性质的 对象 抽象称为 类

    //封装：将属性和行为作为一个整体 并将属性和行为加以权限控制

    //通过圆类 创建具体的圆（对象）
    //实例化 （通过一个类 创建一个对象的过程）
    Circle c1;

    //给圆对象的 属性 进行赋值
    c1.r = 10;

    cout << "perimeter of circle: " << c1.perimeter() << endl;

    return 0;
}