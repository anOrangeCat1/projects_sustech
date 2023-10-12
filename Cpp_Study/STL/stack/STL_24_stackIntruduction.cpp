#include <iostream>
using namespace std;
#include <stack>

//栈容器 符合先进后出
//栈 不允许有遍历的行为

//栈可以判断是否为空 empty
//栈可以返回元素个数 size

//入栈 push
//出栈 pop

//栈stack容器常用接口
void test1()
{
    //特点 符合先进后出的数据结构
    stack<int> s;

    //入栈
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);

    //只要栈不为空 查看栈顶 并且执行出栈操作
    while (!s.empty())
    {
        //查看栈顶元素
        cout << "top of stack: " << s.top() << endl;

        //出栈
        s.pop();
    }

    cout << "size of stack: " << s.size() << endl;
}

int main()
{
    test1();

    return 0;
}

//总结
/*
入栈 -- push
出栈 -- pop
返回栈顶 -- top
判断栈是否为空 -- empty
返回栈大小 -- size
*/