#include "manager.h"

//构造函数
Manager::Manager(int id, string name, int deptid)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = deptid;
}

//显示个人信息
void Manager::showInfo()
{
    cout << "Id: " << this->m_Id
         << "\tName: " << this->m_Name
         << "\tDepartment: " << this->getDeptName()
         << "\tDuty: Obey Boss and Manage Employee" << endl;
}

//获取岗位名称
string Manager::getDeptName()
{
    return string("Manager");
}