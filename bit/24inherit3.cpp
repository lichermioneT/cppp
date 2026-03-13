#include <iostream>
using namespace std;


int main()
{




  return 0;
}

// 学管理系统
// 学生，老师，宿舍阿姨，保安大叔， 信息有冗余的
// person, 都继承自person
// 继承就是为了实现代码的复用的
// 类之间的复用的

// 访问限定符号
class person 
{
public:
void print()
{
  cout<< "_name " << _name <<endl;
  cout<< "_age  " << _age  <<endl;
}

protected:
  string _name = " peter";
  int _age = 18;
};

class stu : public person 
{

protected:
  int _stuid;
};


class tea : public person 
{
protected:
  int _jobid;
};

void test()
{
  person s;
  s.print();
  
  stu s1;
  s.print();

  tea s2;
  s2.print();
} 

// 基类和父类复制关系
// 子类和父类之间的赋值规则
// 子类给父类：对象，指针，引用。三个的
//  切片或者切割。把父类存在的东西都给它，子类自己存在的就切断了
//  父类的一部分切出来的！！
//  赋值只取父类存在的部分
//  指针就是根据父类的类型指向
//  引用也是一样的,指向父类类型的引用的

// 反过来呢？行不行呢？
// 指针的话，需要强制类型转的.
//
// 继承中的作用域
// 隐藏登场。
// 不同的作用域了，同名的函数和变量的。
//  父类和子类同名的成员，子类隐藏了父类的成员的
//  需要访问父类的成员，指定作用域就行了的
//  重定义或者隐藏，一个意思的。函数只需函数名 一样就行的，不需要管参数的
// 记住重载是在同一个作用域的
//
// 指定去调用的时候需要指定 作用域的。
