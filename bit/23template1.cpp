
 #include<iostream>

// #include<cstring>

// using std::cout;
// using std::endl;
// // #define N 1000


// // 非类型模版参数
// // 非类型模版参数是常量，不然怎么做数组的初始化参数呢
// template<class T, int N = 55>
// class array
// {
// private:
//     T _a[N];
// };

// // 不能做非类型模版参数的数据类型
// // float double
// // 自定义类型
// // 基本上都是整形，int或者char类型的

// // array数组


// // 模版特化
// // 特殊类型特殊处理

// /*
// template<class T>
// bool isEqual(T& left, T& right)
// {
//     return left == right;
// }
// */

// template<typename T>
// bool IsEqual(T left, T right)
// {
//     return left == right;
// }

// // 函数模板特化 for const char*
// template<>
// bool IsEqual<const char*>(const char* left, const char* right)
// {
//     return strcmp(left, right) == 0;
// }


// // 类模版特化
// template<class T1, class T2>
// class Data
// {

// public:
//     Data()
//     {
//         cout<< " Data<T1, T2> " <<endl;
//     }
// private:
//     T1 _d1;
//     T2 _d2;
// };

// // 全特化
// template<>
// class Data<int, char>
// {
// public:
//     Data()
//     {
//         cout<< " Data<int, char> " <<endl;
//     }
// private:
//     int _d1;
//     char _d2; 
// };

// // 偏特化
// template<class T2>
// class Data<int, T2>
// {
// public:
//     Data()
//     {
//         cout<< " Data<int, T2> " <<endl;
//     }

// private:
//     int _d1;
//     T2 _d2;
// };

// template<class T1, class T2>
// class Data<T1*, T2*>
// {
// public:
//     Data()
//     {
//         cout<< " Data<T1*, T2*> " <<endl;
//     }

// private:
// };

// template<class T1, class T2>
// class Data<T1&, T2&>
// {
// public:
//     Data()
//     {
//         cout<< " Data<T1&, T2&> " <<endl;
//     }

// private:
// };



// int main()
// {

// // 非类型模版参数
// /*
//     array<int> a;
//     cout<< sizeof(a) <<endl;

//     array<int, 20> a1;
//     cout<< sizeof(a1) << endl;

//     array<int, 300> a2;
//     cout<< sizeof(a2) << endl;
// */

// // 模版的特化

// /*
//     int a = 10;
//     int b = 10;
//     cout<< isEqual<int>(a, b) <<endl;

//     char* p1 = "hello";
//     char* p2 = "world";
// */

// /*
//     Data<int, int> d1;
//     Data<int, char> d2; 
//     Data<char, char> d3; 
//     Data<int*, char*> d4;
//     Data<int&, char&> d5;
// */


// // 模版分离编译
// // 工程中，声明放.h, 定义放在.cpp里面
// // 为什么分离编译，方便查看和维护

// // 模版不能分离编译
// // 为什么呢？

// // 预处理，展开头文件，宏替换，条件编译，去掉注释 func.i 
// // 编译，检查语法，生成汇编代码  func.s
// // 汇编,汇编代码转成二进制的机器码。 func.o
// // 链接，a.out 

// // 链接
// // 模版类型
//     return 0;
// }


#include <iostream>
#include <cstring>
using namespace std;

// 非类型模版参数
/*
#define N 100
template<class T>
class Array
{
public:

private:
    T _a[N];
};
*/

template<class T, size_t N>
class Array
{
public:

private:
    T _a[N];
};


template<class T>
bool IsEqual(const T& left, const T& right)
{
    return left == right;
}

template<>
bool IsEqual<char*>(char* const& left, char* const& right)
{
    return strcmp(left, right) == 0;
}



template<class T1, class T2>
class Data
{
public:
    Data()
    {
        cout<< "原模版Data<T1, T2>" <<endl;
    }

private:
    T1 _d1;
    T2 _d2;
};

template<>
class Data<int, char>
{
public:
    Data()
    {
        cout<< "全特化版本: Data<int, char>" <<endl;
    }
private:
    int _d1;
    char _d2;
};

template<class T2>
class Data<int, T2>
{
public:
    Data()
    {
        cout<< "偏特化版本:Data<int, T2>" <<endl;
    }

private:
    int _d1;
    T2 _d2;
};

template<class T1, class T2>
class Data<T1*, T2*>
{
public:
    Data()
    {
      cout<< "片特化Data<T1*, T2*>" <<endl;
    }
private:
    T1 _d1;
    T2 _d2;
};



int xain()
{



// 非类型模版参数
// 定义一个静态定长的数组
    // 不能随意更改数组的大小
    // Array<int> a1;
    // Array<int> a2;

// 非类型模版参数是常量，不然怎么做数组的长度
    // Array<int, 10> a1;
    // Array<int, 20> a2;
    // Array<int, 30> a3;

    // cout<< sizeof(a1) <<endl;
    // cout<< sizeof(a2) <<endl;
    // cout<< sizeof(a3) <<endl;

// 浮点数、类对象以及字符串是不允许作为非类型模板参数的。
// 基本上都是整型,基本上都是int

// array是一个固定的数组
// vector是可以改变的数组



// 模版的特化

    // int a = 0;
    // int b = 10;
    // cout<< IsEqual(a, b) <<endl;

// // 针对模型类型特殊化处理
//     const char* p1 = "hello";
//     const char* p2 = "world";
//     cout << IsEqual(p1, p2) <<endl;


 

// 全特化版本
// 偏特化版本
    // Data<int, int> d1;
    // Data<int, char> d2;
    // Data<int ,double> d3;
    // Data<char*, int*> d4;



// 模板分离编译
    // 在项目工程中，一般将函数或者类的声明放到.h，函数或者类的定义放到.cpp里面
    // 方便查看或者维护

    // 模版不能分离编译
    // 为什么？

// 预处理：宏替换，头文件展开，取消注释，条件编译
// 编译：语法检查，生成汇编代码
// 汇编：汇编代码转出二进制代码
// 链接：链接起来。
        // 模版函数找不到，为什么呢？
    
    // ✅ C++ 的确是“每个 .cpp 自己走自己”的，互相之间在编译阶段互不关心。
    // ✅ 只有到 链接阶段，不同 .cpp 生成的 .o 文件才会合在一起。

// 解决问题
// template class Data<int, int>;
// template class Data<double, char>;


// 非类型模版参数
// 模版特例化
// 模版分离编译链接



    return 0;
}

