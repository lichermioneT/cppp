#include <iostream>
#include <string>
using namespace std;

class A
{
public:
  int _a;

  void test(int a = 100)
  {
    cout<< "基类的test(int a = 100)的函数 " << a << endl;
  }
};

class B : public A
{
public:
  int _b;
  string  _a;
  void test(char a = 'a')
  {
    cout<< "基类的test(char a = 'a')的函数 " << a << endl;
  }
};


int main()
{
  B b;
  b.test();
  b.A::test();
  return 0;
}
