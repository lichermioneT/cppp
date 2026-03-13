// poly- = 多

// -morph = 形态、形式

// -ism = 表示一种性质或现象


#include <iostream>
using namespace std;

class A
{

};

class B : public A
{

};

class person
{
public:
    virtual void BuyTicket()
    {
        cout<< "成人票：全价" <<endl;
    }
};


class student : public person
{
public:
    virtual void BuyTicket()
    {   
        cout<< "学生票：半价" <<endl;
    }
};

void func(person& p)
{
    cout<< "引用" <<endl;
    p.BuyTicket();  
}

void func2(person* p)
{   
    cout<< "取地址" <<endl;
    p->BuyTicket();
}

void func3(person p)
{
    p.BuyTicket();
}


class D
{
public: 
    virtual ~D() // 析构函数的函数名会被处理成destructor
    {
        cout<< "~D" <<endl;
    }
};

class d : public D
{
public:
    virtual ~d() // 析构函数的函数名会被处理成destructor
    {
        cout<< "~d" <<endl;
    }
};

void test()
{

    {
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
            B*p = new B;
            p->test();
 
    }
}

// 抽象类
// 不能实例化出对象，就好像现实生活中不存在的东西
class E
{
public:
    virtual void dirve() = 0; // 纯虚函数，不需要实现的
};

class F : public E
{
public:
    virtual void dirve()
    {   
        // 重写了才能实例化出对象
        cout<< " dirve " <<endl;
    }
};


class G
{
public:
    virtual void Func()
    {
        cout<< " hello world " <<endl;
    }

    virtual void Func2()
    {
        cout<< " hello world2 " <<endl;
    }

    virtual void Func3()
    {
        cout<< " hello world3 " <<endl;
    }

    virtual void Func4(int x = 55)
    {
        cout<< " hello world4 " <<endl;
    }
    
private:
    int _g = 33;
};

class F : public G
{
public:
    virtual void Func()
    {
        cout<< " ll " <<endl;
    }
};


int main()
{

// 虚函数
// 满足多态的条件：跟对象有关，执行那个对象就调用那个对象
// 不满足多态：对类型有关，    

    // person p1;
    // student s1;

    // func(p1);
    // func(s1);

    // func2(&p1);
    // func2(&s1);

    // func3(p1);
    // func3(s1); // 这里存在切片吧。


// 同样一个动作，不同的对象执行的效果不一样的
// 多态的条件
// 1.虚函数的重写。virtual修饰成员方法。
// vitual关键字，可以修饰成员方法，为了完成虚函数的重写，满足多态的条件
    // 菱形继承完成虚继承，解决二义性

// 派生类函数：返回值，函数名，函数参数。
// 基类的指针或者引用去调用虚函数

// 满足多态跟指向的对象有关，指向哪个对象就是调用它的虚函数
// 不满足多态，跟调用对象的类型有关，类型是什么就是谁方法。


// 虚函数重写的例外
// 协变：返回值不同，
// 即基类虚函数返回基类对象的指针或者引用，
// 派生类虚函数返回派生类对象的指针或者引用时，称为协变。（了解）

// 基类的virtual是虚函数
// 派生类可以不行，但是不推荐


// 析构函数的重写
// 指向谁就调用谁

    // D D1;
    // d d1;

    // D* p1 = new D;
    // delete p1;

    // d* p2 = new d;
    // delete p2;

// override修饰虚函数
// final修饰虚函数（不能被重写），修饰类（不能被继承）

// override,检查是否重写了
// 就是为了检查virtual关键字

// 纯虚函数不能实例化出对象

    // F f;
    // f.dirve();

// 1.纯虚函数是强制派生类重写（override是检查）
// 2.表示抽象类。（在现实生活没有对应的实体的）



// 多态的原理

    // cout<< sizeof(G) <<endl;
    // G里面多了一个指针，虚函数表指针（虚标指针）。其实就是一个指针数组。
    // 指针指向一个数组

// 不同对象的虚函数表里面找虚函数   
// （切片实现的了）


// 虚函数表

// 虚函数存在哪儿？  代码段。
// 虚函数表存在哪儿？ 代码段、常量区。

// 同类型共用一个虚函数表

// 静态绑定，编译时确定函数的地址

// 动态绑定，运行时；运行时到虚标中找虚函数地址


// 单继承和多继承的虚表
// 打印虚表
    



// 对象模型
// 虚函数表
    












    return 0;
}
