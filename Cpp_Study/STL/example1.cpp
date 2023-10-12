#include <iostream>
using namespace std;
#include <vector>
#include <deque>
#include <algorithm>
#include <string>
#include <ctime>

//选手类
class Person
{
public:
    string m_Name;
    int m_Score;

    Person(string name, int score)
    {
        this->m_Name = name;
        this->m_Score = score;
    }
};

void creatPerson(vector<Person> &v)
{
    string nameSeed = "ABCDE";
    for (int i = 0; i < 5; i++)
    {
        string name = "Player";
        name += nameSeed[i];
        int score = 0;

        Person p(name, score);

        //将创建的Person对象 放入到容器中
        v.push_back(p);
    }
}

//打分
void setScore(vector<Person> &v)
{
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        //将评委的分数放到deque容器中
        deque<int> d;
        for (int i = 0; i < 10; i++)
        {
            int score = rand() % 41 + 60; // 60 ~ 100
            d.push_back(score);
        }

        // cout << "Name: " << it->m_Name << "  Score: " << endl;
        // for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
        // {
        //     cout << *dit << " ";
        // }
        // cout << endl;

        //排序
        sort(d.begin(), d.end());

        //去处最高和最低分
        d.pop_back();
        d.pop_front();

        //取平均分
        int sum = 0;
        for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
        {
            sum += *dit; //累加每个评委的分数
        }

        int avg = sum / d.size();

        //将平均分 赋值给选手身上
        it->m_Score = avg;
    }
}

void showScore(vector<Person> &v)
{
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "Name: " << it->m_Name << "Average Score: " << it->m_Score << endl;
    }
}

int main()
{
    //随机数种子
    srand((unsigned int)time(NULL));

    // 1.创建5名选手
    vector<Person> v;
    creatPerson(v);

    // 2.给5名选手打分
    setScore(v);
    showScore(v);

    // 3.显示最后得分

    return 0;
}