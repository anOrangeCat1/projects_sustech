/*
C++中对文件操作需要包含头文件<fstream>

文件类型分为两种
1. 文本文件
2. 二进制文件

操作文件的三大类
1.ofstream: 写操作
2.ifstream: 读操作
3.fstream:  读写操作

文本文件
写文件步骤：
1.包含头文件
#include <fstream>
2.创建流对象
ofstream ofs;
3.打开文件
ofs.open("文件路径",打开方式);
4.写数据
ofs<<"写入的数据";
5.关闭文件
ofs.close();

文件打开方式
ios::in      为读文件而打开文件
ios::out     为写文件而打开文件
ios::ate     初始位置: 文件尾
ios::app     追加方式写文件
ios::trunc   如果文件存在先删除 再创建
ios::binary  二进制方式

文件打开方式可以配合使用 利用|操作符
例如: 用二进制方式写文件: ios::binary|ios::out
*/
#include <iostream>
using namespace std;
#include <fstream> //头文件包含

//文本文件 写文件

void test1()
{
    // 1.包含头文件 fstream

    // 2.创建流对象
    ofstream ofs;

    // 3.指定打开方式
    ofs.open("test.txt", ios::out);

    // 4.写内容
    ofs << "Name: Mike" << endl;
    ofs << "man" << endl;
    ofs << "Age: 18" << endl;

    // 5.关闭文件
    ofs.close();
}

int main()
{
    test1();

    return 0;
}