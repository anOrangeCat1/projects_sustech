#include <iostream>
using namespace std;

//多态案例2 制作饮品
class AbstractDrinking
{
public:
    //煮水
    virtual void Boil() = 0;

    //冲泡
    virtual void Brew() = 0;

    //倒入杯中
    virtual void PourInCup() = 0;

    //加入辅料
    virtual void PutSomething() = 0;

    //制作饮品
    void makeDrink()
    {
        Boil();
        Brew();
        PourInCup();
        PutSomething();
    }
};

//制作咖啡
class Coffee : public AbstractDrinking
{
    //煮水
    virtual void Boil()
    {
        cout << "Coffee: Boil" << endl;
    }

    //冲泡
    virtual void Brew()
    {
        cout << "Coffee: Brew" << endl;
    }

    //倒入杯中
    virtual void PourInCup()
    {
        cout << "Coffee: PourInCup" << endl;
    }

    //加入辅料
    virtual void PutSomething()
    {
        cout << "Coffee: PourSomething" << endl;
    }
};

//制作茶
class Tea : public AbstractDrinking
{
    //煮水
    virtual void Boil()
    {
        cout << "Tea: Boil" << endl;
    }

    //冲泡
    virtual void Brew()
    {
        cout << "Tea: Brew" << endl;
    }

    //倒入杯中
    virtual void PourInCup()
    {
        cout << "Tea: PourInCup" << endl;
    }

    //加入辅料
    virtual void PutSomething()
    {
        cout << "Tea: PourSomething" << endl;
    }
};

//制作函数
void doWork(AbstractDrinking *abs)
{
    abs->makeDrink();
    delete abs; //释放
}

void test1()
{
    //制作咖啡
    doWork(new Coffee); // AbstractDrinking abs = new Coffee;

    cout << "--------------------------------" << endl;

    //制作茶
    doWork(new Tea);
}

int main()
{
    test1();

    return 0;
}