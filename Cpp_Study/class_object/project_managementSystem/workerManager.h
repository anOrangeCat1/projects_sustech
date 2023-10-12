#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

//创建管理类
//管理类负责的内容如下:
/*
1. 与用户的沟通菜单界面
2. 对职工增删改查的操作
3. 与文件的读写交互
*/

//将文件中内容读取到程序中
//构造函数初始化数据分为3种
/*
1.第一次使用 文件未创建
2.文件存在 但是数据被用户清空
3.文件存在 而且保存职工的所有数据
*/

class WorkerManager
{
public:
    //成员变量
    //记录职工人数
    int m_EmpNum;

    //职工数组指针
    Worker **m_EmpArray;

    //判断文件是否为空
    bool m_FileIsEmpty;

    //成员函数
    //构造函数
    WorkerManager();

    //展示菜单
    void Show_Menu();

    //添加职工
    void Add_Emp();

    //保存文件
    void save();

    //退出系统
    void Exit_System();

    //析构函数
    ~WorkerManager();
};