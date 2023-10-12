#include <iostream>
using namespace std;

//占位参数
//返回值类型 函数名(数据类型){}

//目前阶段占位参数还用不到 后面会用到
//占位参数 还可以有默认参数
void func(int a, int = 10)
{
    cout << "This is func." << endl;
}

int main()
{
    func(10);
}