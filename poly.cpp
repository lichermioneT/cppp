#include <iostream>
using namespace std;

class E
{
public:
  virtual void test1()
  {
    cout<< "lic" <<endl;
  }

  virtual void test2()
  {
    cout<< "lic" <<endl;
  }

  virtual void testr3()
  {
    cout<< "lic" <<endl;
  }


private:
  int _a;
  char _b;
};
// 0-7
// 8-11
// 12
// 16

class F : public E
{
public:
  virtual void test1()
  {
    cout<< "..." <<endl;
  }

  virtual void test5()
  {
    cout<< "......" <<endl;
  }
};


int main()
{
  cout<< sizeof(E) <<endl;
  cout<< sizeof(F) <<endl;


  return 0;
}


class student
{
public:
  virtual  void buyTicket()
  {
    cout<< "学生价--半价"<<endl;
  }
};

class person : public student 
{
public:
  virtual void buyTicket()
  {
    cout<< "成人价--全价"<<endl;
  }
};

void test1(student& p)
{
  p.buyTicket();
}

void test2(student* p)
{
  p->buyTicket();
}

void test3()
{
  student s;
  person p;
  test1(s);
  test1(p);
  cout<<endl;

  test2(&s);
  test2(&p);
}


class D final
{
public:
  void test()
  {
    cout<< "这个类不能够被继承下去的"<<endl;
  }
};

class C
{
public:
  virtual void test() final 
  {
    cout<< "这个方法不能够被派生类进行重写的" <<endl;
  }
};

class A
{
public:
  virtual ~A()
  {
    cout<< "A的析构函数" <<endl;
  }
};

class B : public A
{
public:
  virtual~B()
  {
    cout<< "B的析构函数" <<endl;
  }
};

void test4()
{
// 顺序 
// 
  A* p1 = new A;
  A* p2 = new B;

  delete p1; // A直接进行析构就行了
  delete p2; // 先析构B，然后析构A
}
