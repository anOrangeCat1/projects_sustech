#include <iostream>
using namespace std;

//实现 通用对数组进行排序的函数
//规则 从大到小
//算法 选择排序
//测试 char 数组  int 数组

//交换函数模板
template <typename T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

//排序算法
template <typename T>
void mySort(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int max = i; //认定最大值的下标
        for (int j = i + 1; j < len; j++)
        {
            //认定的最大值 比 遍历的数值 要小 说明 j下标的元素 才是真正的最大值
            if (arr[max] < arr[j])
            {
                max = j;
            }
        }
        if (max != i)
        {
            //交换max和i元素
            mySwap(arr[max], arr[i]);
        }
    }
}

//提供打印数组模板
template <typename T>
void printArray(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
}

void test1()
{
    //测试char数组
    char charArr[] = "badcfe";
    int len = sizeof(charArr) / sizeof(char);

    mySort(charArr, len);

    printArray(charArr, len);
}

void test2()
{
    //测试int数组
    int intArr[] = {7, 5, 1, 3, 9, 2, 4, 6, 8};
    int len = sizeof(intArr) / sizeof(int);

    mySort(intArr, len);

    printArray(intArr, len);
}

int main()
{
    test1();

    cout << endl;
    
    test2();

    return 0;
}