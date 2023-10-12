//实现一个通用的数组类 要求如下:
/*
1. 可以对内置数据类型以及自定义数据类型的数据进行存储
2. 将数组中的数据存储到 堆区
3. 构造函数中可以传入数组的 容量
4. 提供对应的 拷贝构造函数 以及 operator= 防止浅拷贝问题
5. 提供 尾插法 和 尾删法 对数组中的数据进行增加和删除
6. 可以通过 下标 的方式访问数组中的元素
7. 可以获取数组中当前 元素个数 和 数组的容量
*/

//自己通用的数组类
#pragma once
#include <iostream>
using namespace std;

template <class T>
class MyArray
{
private:
    T *pAddress; //指针指向堆区开辟的数组

    int m_Capacity; //数组容量

    int m_Size; //数组大小

public:
    //有参构造
    MyArray(int capacity)
    {
        // cout << "Parameter Constructor" << endl;
        this->m_Capacity = capacity;
        this->m_Size = 0;
        this->pAddress = new T[this->m_Capacity];
    }

    //拷贝构造
    MyArray(const MyArray &arr)
    {
        // cout << "Copy Constructor" << endl;
        this->m_Capacity = arr.m_Capacity;
        this->m_Size = arr.m_Size;
        // this->pAddress = arr.pAddress; 浅拷贝

        this->pAddress = new T[arr.m_Capacity];

        //将arr中数据拷贝过来
        for (int i = 0; i < this->m_Size; i++)
        {
            this->pAddress[i] = arr.pAddress[i];
        }
    }

    // operator= 防止浅拷贝问题 a = b = c
    MyArray &operator=(const MyArray &arr)
    {
        // cout << "Operator= Overloading" << endl;
        //先判断原来堆区是否有数据 如果有 先释放
        if (this->pAddress != NULL)
        {
            delete[] this->pAddress;
            this->pAddress = NULL;
            this->m_Capacity = 0;
            this->m_Size = 0;
        }

        //深拷贝
        this->m_Capacity = arr.m_Capacity;
        this->m_Size = arr.m_Size;
        this->pAddress = new T[arr.m_Capacity];

        //将arr中数据拷贝过来
        for (int i = 0; i < this->m_Size; i++)
        {
            this->pAddress[i] = arr.pAddress[i];
        }

        return *this;
    }

    //尾插法
    void Push_Back(const T &val)
    {
        //判断容量是否等于大小
        if (this->m_Capacity == this->m_Size)
        {
            cout << "No Capacity" << endl;
            return;
        }

        this->pAddress[this->m_Size] = val;
        this->m_Size++;
    }

    //尾删法
    void Pop_Back()
    {
        //让用户访问不到最后一个元素 即为尾删
        if (this->m_Size == 0)
        {
            return;
        }

        this->m_Size--;
    }

    //通过下标方式访问数组中元素
    //重载中括号
    T &operator[](int index)
    {
        return this->pAddress[index];
    }

    //返回数组容量
    int getCapacity()
    {
        return this->m_Capacity;
    }

    //返回数组大小
    int getSize()
    {
        return this->m_Size;
    }

    //析构函数
    ~MyArray()
    {
        // cout << "Desturctor" << endl;
        if (this->pAddress != NULL)
        {
            delete[] this->pAddress;
            this->pAddress = NULL;
        }
    }
};