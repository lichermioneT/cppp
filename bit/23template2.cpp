#include <iostream>
#include <cstring>


// 模板的偏特化
//
template<class T>
bool isEqual(const T& left, const T& right)
{
  return  left == right;
}

template<>
bool isEqual<char*>(const char*& left, const char& right)
{
  return strcmp(left, right) == 0; 
}

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

