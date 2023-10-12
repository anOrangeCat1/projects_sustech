#include <iostream>
using namespace std;

//类做友元

class Building;

class GoodGay
{
public:
    Building *building;

    GoodGay();

    void visit(); // 参观函数 访问Building中的属性
};

class Building
{
    friend class GoodGay; // GoodGay类是本类的好朋友 可以访问本类中的私有成员

public:
    string m_SittingRoom; //客厅

    Building();

private:
    string m_BedRoom; //卧室
};

//类外写成员函数
Building::Building()
{
    m_SittingRoom = "SittingRoom";
    m_BedRoom = "BedRoom";
}

GoodGay::GoodGay()
{
    //创建一个建筑物的对象
    building = new Building;
}

void GoodGay::visit()
{
    cout << "GoodGay is visiting: " << building->m_SittingRoom << endl;

    cout << "GoodGay is visiting: " << building->m_BedRoom << endl;
}

void test1()
{
    GoodGay gg;
    gg.visit();
}

int main()
{
    test1();

    return 0;
}