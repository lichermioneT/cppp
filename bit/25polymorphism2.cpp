#include <iostream>
using namespace std;
// 多态是在不同继承关系的类对象，去调用同一函数，产生了不同的行为。

class Person {
public:
 virtual void BuyTicket() { cout << "买票-全价" << endl; }
};
class Student : public Person {
public:
 virtual void BuyTicket() { cout << "买票-半价" << endl; }
};

void Func(Person& p)
{ p.BuyTicket(); }

int main()
{
    Person ps;
    Student st;

    Func(ps);
    Func(st);



  return 0;
}

// 多态，不同的人做，实现不同的效果的。
// 支付宝抢红包的。

//1.通过父类的指针和引用调用虚函数
//2.被调用的函数必须是虚函数，派生类必须重新写虚函数

//虚函数
//返回值，函数名，参数一样的。虚函数的。
