#include "workerManager.h"

WorkerManager::WorkerManager()
{
    //文件不存在
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //读文件

    if (!ifs.is_open())
    {
        cout << "There is no file!" << endl;
        //初始化属性
        //初始化人数 为0
        this->m_EmpNum = 0;

        //初始化指针 为空
        this->m_EmpArray = NULL;

        //初始化文件是否为空
        this->m_FileIsEmpty = true;

        ifs.close();
        return;
    }
}

void WorkerManager::Show_Menu()
{
    cout << "-----------------------------------" << endl;
    cout << "---------Management System---------" << endl;
    cout << "----------0. Exit System-----------" << endl;
    cout << "----------1. Add Employee----------" << endl;
    cout << "----------2. Show Information------" << endl;
    cout << "----------3. Delete Employee-------" << endl;
    cout << "----------4. Modify Information----" << endl;
    cout << "----------5. Find Employee---------" << endl;
    cout << "----------6. Sort by Number--------" << endl;
    cout << "----------7. Clear All Files-------" << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;
}

void WorkerManager::Add_Emp()
{
    cout << "Input the number of employees added: " << endl;

    int addNum = 0; //保存用户的输入数量
    cin >> addNum;
    cin.get();

    if (addNum > 0)
    {
        //添加
        //计算添加新的空间大小 新的人数
        int newSize = this->m_EmpNum + addNum; //新空间大小 = 原来记录人数 + 新增人数

        //开辟新空间
        Worker **newSpace = new Worker *[newSize];

        //将原来数据下拷贝到新空间下
        if (this->m_EmpArray != NULL)
        {

            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //添加新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;         //职工编号
            string name;    //职工姓名
            int deptSelect; //部门选择

            cout << "Input the " << i + 1 << " employee's id:" << endl;
            cin >> id;

            cout << "Input the " << i + 1 << " employee's name:" << endl;
            cin >> name;

            cout << "Select the department: " << endl;
            cout << "1. Employee" << endl;
            cout << "2. Manager" << endl;
            cout << "3. Boss" << endl;
            cin >> deptSelect;

            Worker *worker = NULL;
            switch (deptSelect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            }

            //将创建的职工指针保存到数组中
            newSpace[this->m_EmpNum + i] = worker;
        }

        //释放原有的空间
        delete[] this->m_EmpArray;

        //更改新空间指向
        this->m_EmpArray = newSpace;

        //更新职工人数
        this->m_EmpNum = newSize;

        //保存数据到文件中
        this->save();

        //提示添加成功
        cout << "Add " << addNum << " new people successfully!" << endl;
    }
    else
    {
        cout << "Wrong Number!" << endl;
    }

    //按任意键清屏回到上级目录
}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); //用输出方式打开文件 -- 写文件

    //将每个人的数据写入到文件中
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }

    //关闭文件
    ofs.close();
}

void WorkerManager::Exit_System()
{
    cout << "System Exits" << endl;
    cout << "See You Next Time~" << endl;
    exit(0); //退出程序
}

WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}