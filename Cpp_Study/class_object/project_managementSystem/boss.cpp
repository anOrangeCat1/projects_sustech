#include "boss.h"

//构造函数
Boss::Boss(int id, string name, int deptid)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = deptid;
}

//显示个人信息
void Boss::showInfo()
{
    cout << "Id: " << this->m_Id
         << "\tName: " << this->m_Name
         << "\tDepartment: " << this->getDeptName()
         << "\tDuty: Manage Everything" << endl;
}

//获取岗位名称
string Boss::getDeptName()
{
    return string("Boss");
}
