#include <iostream>
using namespace std;
// 多态是在不同继承关系的类对象，去调用同一函数，产生了不同的行为。

// 静态绑定：编译 时
// 动态绑定：运行 时
//


// 单继承和多继承的虚表
// 继承的时候虚函数表也会继承的。
// 重写的就重写，不重写的指向基类的函数 

class Base1 
{
public:
 virtual void func1() {cout << "Base1::func1" << endl;}
 virtual void func2() {cout << "Base1::func2" << endl;}
private:
 int b1;
};
class Base2 
{
public:
 virtual void func1() {cout << "Base2::func1" << endl;}
 virtual void func2() {cout << "Base2::func2" << endl;}
private:
 int b2;
};
class Derive : public Base1, public Base2 
{
public:
 virtual void func1() {cout << "Derive::func1" << endl;}
 virtual void func3() {cout << "Derive::func3" << endl;}
private:
 int d1;
};

typedef void(* VF_PTR)(); // 函数指针
void print_VFTable(VF_PTR* ptable)
{
  for(size_t i = 0; ptable[i] != 0; ++i)
  {
    printf("vftable[%zu] : %p \n", i, ptable[i]);
  }
  cout<<endl;
}


// 先继承的放到前面了。
//
// 内联函数没有地址，
// 静态函数没有this值，不能够访问对象的

int main()
{
  /*
   *Base1 b;
   *Derive d;
   *print_VFTable((VF_PTR*)(*(int*)&b));
   */

/*
 *    Person ps;
 *    Student st;
 *
 *    Func(ps);
 *    Func(st);
 */
  return 0;
}

// 多态，不同的人做，实现不同的效果的。
// 支付宝抢红包的。

//1.通过父类的指针和引用调用虚函数
//2.被调用的函数必须是虚函数，派生类必须重新写虚函数

//虚函数
//返回值，函数名，参数一样的。虚函数的。



//1.虚函数重新
//2.父类的指针或者引用去调用虚函数的
//满足多态：根指向的对象有关，指向那个对象调用，就是他的虚函数。
//父类根据指向的对象进行调用的。
/*
 *class Person 
 *{
 *public:
 * virtual void BuyTicket() { cout << "买票-全价" << endl; }
 *};
 *class Student : public Person 
 *{
 *public:
 * virtual void BuyTicket() { cout << "买票-半价" << endl; }
 *};
 *
 *void Func(Person& p)
 *{ 
 *  p.BuyTicket(); 
 *}
 */



// 协变
// 虚函数重写的特例，返回父类(子类)的引用或者指针。
// 返回父子关系的就行的。

// 虚函数的重写的
// 子类的虚函数，virtual可以不写，不规范的，不建议写的。



// 析构函数呢？是否需要定义成虚函数呢？
// 构造成多态，指向谁，就调用谁的呢。
//
// 因为通过父类指针删除子类对象时，如果析构函数不是虚函数，就会发生析构不完整的问题。
// 为了绝对的安全，C++ 编译器干脆接管了这项工作：只要派生类对象被销毁，我就保证它的基类部分也会被顺带销毁。

class Person {
public:
 virtual ~Person() {cout << "~Person()" << endl;}
};

class Student : public Person {
public:
 virtual ~Student() { cout << "~Student()" << endl; }
};

void test()
{
  Person* p1 = new Person;
  Person* p2 = new Student;
  delete p1;
  delete p2;
}

// 虚函数test，继承下来了，然后去调用func()函数，根据多态的原理，调用派生类B的，
// 虽然这里也有缺省参数，但是不起作用的。
// 所以
// B->1;
class A
{
public:
 virtual void func(int val = 1){ std::cout<<"A->"<< val <<std::endl;}
 virtual void test(){ func();}
};
class B : public A
{
public:
 void func(int val=0){ std::cout<<"B->"<< val <<std::endl; }
};

void test1()
{
 B*p = new B;
 p->test();
}


// 关键字final.
// final修饰对象，不能够被继承的
// final修饰虚函数，虚函数不能够被重写的。
//  构造函数私有，不能够被继承的。
//
//  override检查重写的。检查虚函数的重写。
//  检查派生类的虚函数重写的。

//1.重载：同一个作用域，函数名一样，函数参数类型不一样(个数或者类型不一样的)
//2.重写(覆盖):基类和派生类之间的关系。函数名，参数，返回值必须一样的，两个函数必须是虚函数。协办例外的。重写就是为了多态的。
//3.重定义(隐藏)：基类和派生类，函数名字一样的，基类和派生类的同名函数不是重写，就是重定义的。




// 抽象类，纯虚函数=0；
// 1.强制完成子类去完成重写的
// 2.抽象。就是在显示社会不存在的实体。（car)什么车都去继承它的。
class car 
{
public:
    virtual void test() = 0;
};

class modexy : public car 
{
public:
  virtual void test()
  {
    cout<< "Tesla 值最棒的电动车" <<endl;
  }
};

void test3()
{
  modexy y;
  y.test();
}
// a 
// d
// c
// a
// b


// 虚函数的继承就是：接口继承
// 普通的继承就是：  实现继承


// 多态的实现原理的
// 虚函数表指针：虚表指针的。

class base 
{
public:
  virtual void func1()
  {
    cout<< "func1" <<endl;
  }
  virtual void func2()
  {
    cout<< "func2" <<endl;
  }

private:
  int _a;
};

void test4()
{
  cout<< sizeof(base) <<endl;
}

// 一个指针(存放一个地址)8字节
// 一个int4字节
// 按照最大成员的对其倍数
// 所以是16的。

// 如何实现指向谁，就去调用谁的原理呢？
// 多态是在运行时-到指向的对象的虚表中查
// 找，要调用的虚函数的地址，然后指向的。

// 对象模型
// 虚函数表
// 其它东西
//
// 虚函数是运行的时候查表

class person {
public:
 virtual void BuyTicket() { cout << "买票-全价" << endl; }
};
class student : public person {
public:
 virtual void BuyTicket() { cout << "买票-半价" << endl; }
};

// 现在它根本不知道是那个的虚函数呢？
void Func(person& p) // 传入那个对象，就去那个对象的虚函数表里面去找的。
{
 p.BuyTicket();
}


// 单继承和多继承关系的虚函数表
// 虚函数表，函数指针数组。
// 派生类会拷贝基类的虚函数，然后进行重写(或者不重写的)
//
// 虚表存的指针
// 虚函数存在哪儿？ 代码段 
// 虚函数表呢？     代码段，常量区域的。(只需要存，代码的实现的函数的地址就行了。)    
// 虚表早就生成了的。因为函数已经生成好了的
//
//
