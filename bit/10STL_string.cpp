#include <iostream>
#include <cassert>
#include <cstring>   // C++ 中推荐
#include <string>
// #include <string.h>  // C 语言风格

using namespace std;
template<class T>
class vector
{
public:
    vector()
        :_a(nullptr)
        ,_size(0)
        ,_capacity(0)
    {
        // 无参数不添加信息
    }

    ~vector()
    {
        delete[] _a;
        _a = nullptr;
        _size = _capacity = 0;
    }
    
    // 模版尽量引用和const 用用
    void push_back(const T& x);
    void pop_back();

    // 类里面声明
    // 类外面定义

// 数组下标的operator
// vector重载的[]
    T& operator[](size_t i)
    {
        assert(i < _size);
        return _a[i];
    }

     size_t size()
     {
         return _size;
     }


private:
    T* _a;
    size_t _size;
    size_t _capacity;
};


// 类外面定义
template<class T>
void vector<T>::push_back(const T& x)
{
    if(_size == _capacity)
    {
        size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
        T* temp =  new T[newcapacity];

        if(_a != nullptr)
        {
            memcpy(temp, _a, sizeof(T) * _size);
            delete[] _a;
        }

         _a = temp;
        _capacity = newcapacity;
    }
    
    _a[_size] = x;
    ++_size;
}

template<class T>
void vector<T>::pop_back()
{
    assert(_size);
    --_size;
}

template<class T>
T add(const T& x, const  T& y)
{
    return x + y;
}

int add(const int& x, const int& y)
{
    return x + y;
}

int main()
{
// 泛型编程：使用模版，编写跟类型无关的代码
// 一些函数和类的时候，针对不同的类型需要写出很多重复的代码
// 函数：实现交换int, double,char
// 类：实现一个数据结构stack，stack的多个对象，st1存放int，st2存放double....
// 没有模版之前，针对各种类型，写出不同的类,这些函数和类处理的 逻辑都是一样的，只是处理的对象类型不同

// 函数模版
// template<class T>
// void Swap(T& a, T& b)


// 类模版
// template<class T>
// class stack
// {
// private:
//     T* _a;
//     size_t _size;
    // size_t _capacity;
// };

// 模版原理，编译根据调用函数模版和类模版的类型，实例化出对应的函数和类
// Swap(1, 2)
// Swap('c', 's');
// stack<int> st1;
// stack<double> st2;

    
// 函数重载 + 类和对象（4个默认构造函数 + 运算符重载）+ 泛型编程:模版
// 解决c语言解决不好或者没有解决的问题
// 数据和方法放在一起,类里面天然就是封装了的。还有访问限定符。
// 构造函数和析构函数，c++执着的初始化和自动销毁。

// 熟悉模版语法
// 熟悉模版原理
// 理解基础语法+类和对象+模版



// 重载了[]，不仅可以读，还可以写的。(返回的是&)
// 引用做参数1.改变参数swap函数，2.减少拷贝
// 引用做返回值1.修改返回对象operator[], 2减少拷贝
/*
 *     vector<int> v;
 *     v.push_back(1);
 *     v.push_back(2);
 *     v.push_back(3);
 *     v.push_back(4);
 *  
 *     v.push_back(1);
 *     v.push_back(2);
 *     v.push_back(3);
 *     v.push_back(4);
 *
 *     v.push_back(1);
 *     v.push_back(2);
 *     v.push_back(3);
 *     v.push_back(4);
 *     for(size_t i = 0; i < v.size(); i++)
 *     {
 *       v[i] *= 2;
 *       cout<< v[i] << " ";
 *     }
 *      
 *     cout <<endl;
 *     cout<< v[3] <<endl;
 *     v[3] = 666;
 *     cout<< v[3] <<endl;
 */

// 类一般都是显示实例化
    // add(22, 4); // 隐士实例化
    // add<double>(7.2,99.3); // 显示实例化
    
    // 模版和实际函数名字一样时，调实际函数
    // 能够偷懒就偷懒
/*
 *     string s1;
 *     string s2("hello");
 *     string s3(s2);
 *     string s4(10, 'a');
 *
 *     string s5 = "hello";
 *     string s6 = s2;
 *
 *     cout<< s1 <<endl;
 *     cout<< s2 <<endl;
 *     cout<< s3 <<endl;
 *     cout<< s4 <<endl;
 *     cout<< s5 <<endl;
 *     cout<< s6 <<endl;
 */

    string s1("12345");
    string s2;
    string s3(10, 'x');
    string s4(s3);
    cout<< "s1 " << s1 <<endl;
    cout<< "s2 " << s2 <<endl;
    cout<< "s3 " << s3 <<endl;
    cout<< "s4 " << s4 <<endl;

    
    string s5 = "hello";
    string s6 = s5;

    cout<< "s5 " << s5 <<endl;
    cout<< "s6 " << s6 <<endl;

    cout<< s2 <<endl;
    s2.push_back('6');

    s2 += '7';
    s2 += '8';

    s2.append("910");

    cout<< s2 <<endl;

// 推荐+=
    string li;
    li += "li ";
    li += "hai ";
    li += "jun ";
    cout<< li <<endl;

    string s("123456");

    int val = 0;
    for(size_t i = 0; i < s.size(); i++)
    {
        val *= 10;
        val += (s[i] - '0');
    }
    
    cout<< val <<endl;

    return 0;
}

