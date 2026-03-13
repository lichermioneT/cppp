#include <iostream>
#include <cstring>
using namespace std;

// 


int main()
{

  return  0;
}

// 非类型模板参数的
// 非类型模板参数是常量的，就是一个类型的字面量
// double,自定义类型不行的
// 实际上基本都是int类型的
//
// 模板不一定是类型的。

// 例子指定任意类型参数的数据大小
// Array数据就是指定大小的数组。
template<class T, size_t n>
class Array 
{

private:
  T _a[n];
};

void test()
{
  Array<int, 10> a1;
  Array<int, 100> a2;
}


// 模板的偏特化
//
template<class T>
bool isEqual(const T& left, const T& right)
{
  return  left == right;
}

/*
 *const T&修饰的是T本身
 *const T& == char* const &
 */
template<>
bool isEqual<const char*>(const char* const& left, const char* const & right)
{
  return strcmp(left, right) == 0; 
}

// 特化就是重新写一个模板，不指定类型，函数后面或者，类后面重新类型的
// 特化不指定的类型就放到template的头上，指定的就放到函数或者类的后面去的
// 但是对象或者函数后面都必须写全的，
template<class T1, class T2>
class Data 
{
public:
  Data()
  {
    cout<< " T1, T2" <<endl;
  }
};

template<class T2>
class Data<int,T2>
{
public:
  Data()
  {
    cout<< "int T2" <<endl;
  }
};

template<class T1>
class Data<T1,int>
{
public:
  Data()
  {
    cout<< "T1 int" <<endl;
  }
};
template<>
class Data<int, char>
{
public:
  Data()
  {
    cout<< "int char" <<endl;
  }
};


void test2()
{
  cout<< isEqual<int>(10, 99) <<endl; 
  cout<< isEqual<int>(10, 10) <<endl; 
  cout<< isEqual<const char *>("asfsadf", "bcd") <<endl; 

  Data<int, char> d1;
  Data<int, char*> d2;
  Data<char*, int> d3;
  Data<int, double> d4;
}

// 模板的分离编译的
// 在工程中，函数或者类的声明放.h, 定义放到.cpp
// 方便维护或者查看的 维护的

// 模板不能够分离编译的
// 因为不能够链接的上去
// 同样是分离编译，普通函数可以，函数模板和类模板不行的

// 1.预处理，去掉注释，宏替换，头文件展开，条件编译 func.i
// 2.编译，检查语法，生成汇编代码   fun.s
// 3.汇编，汇编代码---二进制机器码  fun.o
// 4.链接，就是把全部的.o, .obj文件链接起来的，

// 1.显示实例化
// 2.不要分离编译
