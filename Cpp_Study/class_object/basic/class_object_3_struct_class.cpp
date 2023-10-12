#include <iostream>
using namespace std;

class C1
{
    int a; //默认权限是 私有
};

struct C2
{
    int a; //默认权限是 公共
};

int main()
{
    // struct 和 class 区别
    // struct 默认权限是 公有 public
    // class  默认权限是 私有 private

    C1 c1;
    // c1.a = 100; 不可访问

    C2 c2;
    c2.a = 100;

    return 0;
}