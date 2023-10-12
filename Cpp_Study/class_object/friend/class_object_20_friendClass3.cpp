#include <iostream>
using namespace std;
#include <string>

class Building;

class GoodGay
{
public:
    Building *building;

    GoodGay();

    void visit();  //让visit函数可以访问Building中私有成员
    void visit2(); //让visit函数不可以访问Building中私有成员
};

class Building
{
    //告诉编译器 GoodGay类下的visit成员函数作为本类的好朋友 可以访问私有成员
    friend void GoodGay::visit();

public:
    string m_SittingRoom; //客厅

    Building();

private:
    string m_BedRoom; //卧室
};

//类外实现成员函数
Building::Building()
{
    m_SittingRoom = "SittingRoom";
    m_BedRoom = "BedRoom";
}

GoodGay::GoodGay()
{
    building = new Building;
}

void GoodGay::visit()
{
    cout << "GoodGay is visiting: " << building->m_SittingRoom << endl;

    cout << "GoodGay is visiting: " << building->m_BedRoom << endl;
}

void GoodGay::visit2()
{
    cout << "GoodGay is visiting2: " << building->m_SittingRoom << endl;

    // cout << "GoodGay is visiting2: " << building->m_BedRoom << endl;
}

void test1()
{
    GoodGay gg;
    gg.visit();
    gg.visit2();
}

int main()
{
    test1();

    return 0;
}