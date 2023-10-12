#include <iostream>
using namespace std;
#include <fstream>
#include <string>

//文本文件 读文件
void test1()
{
    // 1.包含头文件

    // 2.创建流对象
    ifstream ifs;

    // 3.打开文件 并且判断是否打开成功
    ifs.open("test.txt", ios::in);

    if (!ifs.is_open())
    {
        cout << "fail to open!" << endl;
        return;
    }

    // 4.读数据
    // 第一种
    // char buf1[1024] = {0};
    // while (ifs >> buf1)
    // {
    //     cout << buf1 << endl;
    // }

    // 第二种
    // char buf2[1024] = {0};
    // while (ifs.getline(buf2, sizeof(buf2)))
    // {
    //     cout << buf2 << endl;
    // }

    // 第三种
    // string buf3;
    // while (getline(ifs, buf3))
    // {
    //     cout << buf3 << endl;
    // }

    // 第四种
    char c;
    while ((c = ifs.get()) != EOF) // EOF end of file
    {
        cout << c;
    }

    // 5.关闭文件
    ifs.close();
}

int main()
{
    test1();

    return 0;
}