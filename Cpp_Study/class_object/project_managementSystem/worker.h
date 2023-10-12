#pragma once
#include <iostream>
#include <string>
using namespace std;

//创建职工抽象类
/*
职工的分类为: 普通员工 经理 老板
将三种职工抽象到一个类(worker)中 利用多态管理不同职工种类
职工的属性: 职工编号 职工姓名 职工所在部门编号
职工的行为: 岗位职责信息描述 获取岗位名称
*/

//职工抽象类
class Worker
{
public:
    //职工编号
    int m_Id;
    //职工姓名
    string m_Name;
    //部门编号
    int m_DeptId;

    //显示个人信息
    virtual void showInfo() = 0;

    //获取岗位名称
    virtual string getDeptName() = 0;
};