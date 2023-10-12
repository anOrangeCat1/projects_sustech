#include <iostream>
using namespace std;
#include "MyArray.hpp"

void printIntArray(MyArray<int> &arr)
{
    for (int i = 0; i < arr.getSize(); i++)
    {
        cout << arr[i] << endl;
    }
}

void test1()
{
    MyArray<int> arr1(5);

    //     MyArray<int> arr3(100);
    //     arr3 = arr1;

    for (int i = 0; i < 5; i++)
    {
        //利用尾插法向数组中插入数据
        arr1.Push_Back(i);
    }

    cout << "print of arr1:" << endl;
    printIntArray(arr1);
    cout << "Capacity of arr1: " << arr1.getCapacity() << endl;
    cout << "Size of arr1: " << arr1.getSize() << endl;

    MyArray<int> arr2(arr1);
    cout << "print of arr2:" << endl;
    printIntArray(arr2);

    //尾删
    arr2.Pop_Back();

    cout << "Capacity of arr2: " << arr2.getCapacity() << endl;
    cout << "Size of arr2: " << arr2.getSize() << endl;
}

//测试自定义数据类型
class Person
{
public:
    string m_Name;
    int m_Age;

    Person(){};
    Person(string name, int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
};

void printPersonArray(MyArray<Person> &arr)
{
    for (int i = 0; i < arr.getSize(); i++)
    {
        cout << "Name: " << arr[i].m_Name << "  Age: " << arr[i].m_Age << endl;
    }
}

void test2()
{
    MyArray<Person> arr(10);

    Person p1("Mike", 77);
    Person p2("Jack", 45);
    Person p3("Amy", 18);
    Person p4("Gill", 30);
    Person p5("Dad", 54);

    //将数据插入到数组中
    arr.Push_Back(p1);
    arr.Push_Back(p2);
    arr.Push_Back(p3);
    arr.Push_Back(p4);
    arr.Push_Back(p5);

    //打印数组
    printPersonArray(arr);

    //打印容量和大小
    cout << "Capacity of arr: " << arr.getCapacity() << endl;
    cout << "Size of arr: " << arr.getSize() << endl;
}

int main()
{
    // test1();
    test2();

    return 0;
}