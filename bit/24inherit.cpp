#include <iostream>
#include <string>
using namespace std;


class Person
{
public:
    void Print()
    {
        cout<< "name:"<< _name <<endl;
        cout<< "_age:"<< _age <<endl;
    }

protected:
    string _name = "peter";
    int _age = 18;
};


class Student : public Person
{

protected:
    int  _stdid;
};

class Teacher : public Person
{

protected:
    int _jobid;
};

class Base 
{
public:    int pub = 0; 
protected: int pro = 1; // 继承的时候可以访问
private:   int pri = 2; // 只能在当前类里面访问数据。继承不能访问数据。
};

class Derived1 : public Base 
{
    // pub -> 还是 public
    // pro -> 还是 protected
    // pri -> 不可访问

public:
   void Test()
    {
        cout << pub << endl;  // ✅ 可以访问，还是 public
        cout << pro << endl;  // ✅ 可以访问，还是 protected
        // cout << pri << endl; // ❌ 不可访问
    }
};

class Derived2 : protected Base 
{   
    // pub -> 变成 protected
    // pro -> 还是 protected
    // pri -> 不可访问

public:
    void Test()
    {
        cout << pub << endl;  // ✅ 可以访问，但变成 protected
        cout << pro << endl;  // ✅ 可以访问，还是 protected
        // cout << pri << endl; // ❌ 不可访问
    }


};

class Derived3 : private Base 
{
    // pub -> 变成 private
    // pro -> 变成 private
    // pri -> 不可访问

public:
    void Test()
    {
        cout << pub << endl;  // ✅ 可以访问，但变成 private
        cout << pro << endl;  // ✅ 可以访问，但变成 private
        // cout << pri << endl; // ❌ 不可访问
    }
};


class father
{
public: int x = 1;
protected: int y = 2;
private: int z = 3;
};

class son1 : public father
{       
public:
    void test()
    {
        cout<< x <<endl;
        cout<< y <<endl;
    }

};

class son2 : protected father
{
public:
    void test()
    {
        cout<< x <<endl;
        cout<< y <<endl;
    }
};

class son3 : private father
{
public:
    void test()
    {
        cout<< x <<endl;
        cout<< y <<endl;
    }
};





int main()
{

// 继承本质类之间的复用

    // Student s;
    // Teacher t;
    // s.Print();
    // t.Print();

// 派生类 ：继承方式 基类
    // 继承方式
    // public:
    // protected:

    // private:

// 类中的私有和保护子啊当前类没有差别 
// 在继承的后的子类中有差别，private的在子类不可见。

    // public>protectde>private
    
// class默认private继承
// struct默认public继承

    // Person p;
    // Student s;

    // // 子类和父类直接的赋值规则
    // // 派生类对象可以赋值给基类的对象/基类的指针/基类的引用。
    // // 切片切割，切片，只能访问继承过来的
    // p = s;
    // Person* ptr = &s;
    // Person& ref = s;    

// 类的作用域
    // 同名时，子类隐藏了父类
    // 隐藏，重定义


    // Derived1 d1;
    // cout<< d1.pub <<endl;
    // d1.Test();

    // Derived2 d2;
    // d2.Test();
    
    // Derived3 d3;
    // d3.Test();


// private:私有变量，只能自己在类里面访问
// protected:继承的时候可以访问，
// public:

    // son1 s1;
    // s1.test();
    // cout<< s1.x <<endl;

// public 继承：像“原样继承”，外部还能用基类的 public。
// protected 继承：继承下来的东西“只留给子类用”，外部访问不到。
// private 继承：继承下来的东西“全变私有”，外部完全访问不到。


// 面向对象的三大特性：封装，继承，多态。
// 实际特性还有抽象，反射


// 派生类可以赋值给基类
// 赋值，指针，引用都可以的
// 继承当做的作用域：隐藏或者作用域
// 派生类的同名成员，成员函数会隐藏基类的同名成员，成员函数


// 六个默认成员函数
// 构造，析构，拷贝，赋值


    return 0;
}
