#include <iostream>
using namespace std;
#include <string>

class Building
{
    // goodGay全局函数是Building的好朋友 可以访问Building类中的私有成员
    friend void goodGay(Building *building);

public:
    string m_SittingRoom; //客厅

    Building()
    {
        m_SittingRoom = "SittingRoom";
        m_BedRoom = "BedRoom";
    }

private:
    string m_BedRoom; //卧室
};

//全局函数
void goodGay(Building *building)
{
    cout << "goodGay is visiting: " << building->m_SittingRoom << endl;

    cout << "goodGay is visiting: " << building->m_BedRoom << endl;
}

void test1()
{
    Building building;
    goodGay(&building);
}

int main()
{
    test1();

    return 0;
}