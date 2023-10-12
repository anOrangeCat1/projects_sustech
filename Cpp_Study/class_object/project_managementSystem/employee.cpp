#include "employee.h"

//构造函数
Employee::Employee(int id, string name, int deptid)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = deptid;
}

//显示个人信息
void Employee::showInfo()
{
    cout << "Id: " << this->m_Id
         << "\tName: " << this->m_Name
         << "\tDepartment: " << this->getDeptName()
         << "\tDuty: Obey Manager" << endl;
}

//获取岗位名称
string Employee::getDeptName()
{
    return string("Employee");
}
