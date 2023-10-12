#pragma once
#include <iostream>
#include "point.h"
using namespace std;

class Circle
{
private:
    int r; //半径

    //在类中可以让另一个类 作为本来的成员
    Point center; //圆心
public:
    void setR(int a);

    int getR();

    void setCenter(Point a);

    Point getCenter();
};