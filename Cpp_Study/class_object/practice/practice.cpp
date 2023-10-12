#include <iostream>
#include "point.cpp"
#include "circle.cpp"
using namespace std;

//点和圆的关系案例

//点类
// class Point
// {
// private:
//     int x;
//     int y;

// public:
//     void setX(int a)
//     {
//         x = a;
//     }

//     int getX()
//     {
//         return x;
//     }

//     void setY(int a)
//     {
//         y = a;
//     }

//     int getY()
//     {
//         return y;
//     }
// };

//圆类
// class Circle
// {
// private:
//     int r; //半径

//     //在类中可以让另一个类 作为本来的成员
//     Point center; //圆心
// public:
//     void setR(int a)
//     {
//         r = a;
//     }

//     int getR()
//     {
//         return r;
//     }

//     void setCenter(Point a)
//     {
//         center = a;
//     }

//     Point getCenter()
//     {
//         return center;
//     }
// };

//判断点和圆关系
void isInCircle(Circle &c, Point &p)
{
    //计算 两点之间距离 的平方
    int distance =
        (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) +
        (c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());

    //计算 半径 的平方
    int rDistance = c.getR() * c.getR();

    if (distance == rDistance)
    {
        cout << "point is on circle." << endl;
    }
    else if (distance > rDistance)
    {
        cout << "point is out of circle." << endl;
    }
    else
    {
        cout << "point is in circle." << endl;
    }
}

int main()
{
    //创建圆
    Circle c;
    Point center;
    center.setX(10);
    center.setY(0);

    c.setR(10);
    c.setCenter(center);

    //创建点
    Point p;
    p.setX(10);
    p.setY(9);

    isInCircle(c, p);
}