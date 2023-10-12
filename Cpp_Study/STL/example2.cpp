#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include <string>
#include <ctime>

//描述
/*
公司招了10名员工(ABCDEFGHIJ) 10名员工进入公司之后 需要指派员工在各部门工作
员工信息有: 姓名 工资组成
部门分为: 策划 美术 研发
随机给10名员工分配部门和工资
通过multimap进行信息的插入 key(部门编号) value(员工)
分部门显示员工信息
*/

#define CEHUA 0
#define MEISHU 1
#define YANFA 2

class Worker
{
public:
    string m_Name;
    int m_Salary;
};

//创建员工
void createWorker(vector<Worker> &v)
{
    string nameSeed = "ABCDEFGHIJ";
    for (int i = 0; i < 10; i++)
    {
        Worker worker;
        worker.m_Name = nameSeed[i];

        worker.m_Salary = rand() % 10000 + 10000; // 10000~19999

        v.push_back(worker); //将员工放到容器中
    }
}

//员工分组
void setGroup(vector<Worker> &v, multimap<int, Worker> &m)
{
    for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++)
    {
        //产生随即部门编号
        int deptId = rand() % 3; // 0 1 2

        //将员工插入到分组中
        m.insert(make_pair(deptId, *it));
    }
}

void showWorkerByGroup(multimap<int, Worker> &m)
{
    cout << "CeHua: " << endl;
    multimap<int, Worker>::iterator pos = m.find(CEHUA);
    int count = m.count(CEHUA); //统计具体人数
    int index = 0;

    for (; pos != m.end() && index < count; pos++, index++)
    {
        cout << "Name: " << pos->second.m_Name << "  Salary: " << pos->second.m_Salary << endl;
    }

    cout << "----------------------------------" << endl;

    cout << "MeiShu: " << endl;
    pos = m.find(MEISHU);
    count = m.count(MEISHU); //统计具体人数
    index = 0;

    for (; pos != m.end() && index < count; pos++, index++)
    {
        cout << "Name: " << pos->second.m_Name << "  Salary: " << pos->second.m_Salary << endl;
    }

    cout << "----------------------------------" << endl;

    cout << "YanFa: " << endl;
    pos = m.find(YANFA);
    count = m.count(YANFA); //统计具体人数
    index = 0;

    for (; pos != m.end() && index < count; pos++, index++)
    {
        cout << "Name: " << pos->second.m_Name << "  Salary: " << pos->second.m_Salary << endl;
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    // 1. 创建员工
    vector<Worker> vWorker;
    createWorker(vWorker);

    ////测试
    // for (vector<Worker>::iterator it = vWorker.begin(); it != vWorker.end(); it++)
    // {
    //     cout << "Name: " << it->m_Name << "  Salary: " << it->m_Salary << endl;
    // }

    // 2. 员工分组
    multimap<int, Worker> mWorker;
    setGroup(vWorker, mWorker);

    // 3. 分组显示员工
    showWorkerByGroup(mWorker);

    return 0;
}