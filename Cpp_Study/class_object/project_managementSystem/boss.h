#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

//经理类
class Boss : public Worker
{
public:
    //构造函数
    Boss(int id, string name, int deptid);

    //显示个人信息
    virtual void showInfo();

    //获取岗位名称
    virtual string getDeptName();
};