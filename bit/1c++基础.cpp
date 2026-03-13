#include <iostream>
using namespace std; // c++库所有东西都在std命名空间里面

// cs 客户端  
// bs 网页端  
// 刷题 多读书
// 剑指offer, 系统， 网络
// 刷题
// 刷题：200道不多。200道加
//

/*
1.命名空间
2.缺省参数（默认参数）
3.函数重载 extern "c" 修饰函数，让函数按照c语言的规则去编译
4.引用
5.临时变量具有常属性
*/


namespace N
{
    int num1 = 55;
    int num2 = 66;
    int add(int x, int y)
    {
        return x + y;
    }
}

void Func(int x = 1, int y = 2, int z = 3)
{
    cout<< "x = " << x <<endl;
    cout<< "y = " << y <<endl;
    cout<< "z = " << z <<endl;
}

void Func2(int x, int y = 2, int z = 3)
{
    cout<< "x = " << x <<endl;
    cout<< "y = " << y <<endl;
    cout<< "z = " << z <<endl;
}

int add(int x, int y)
{
    return x + y;
}

int add(int x, int y, int z)
{
    return x + y + z;
}

int add(int x, int y, double d)
{
    return x + y + (int)d;
}

extern "C"  int sub(int x, int y)
{
    return x = y;
}
// extren "C" int add()
// 按照c语言的规则编译

int main()
{


    // {
    //     using N::num1;
    //     cout<< "N::num1 = "<< num1 <<endl;
    // }
    
    // {
    //     using namespace N;
    //     cout<< "using namespace N = "<< N::num1 <<endl;
    //     cout<< "num1 = " << num1 <<endl;
    //     cout<< "num2 = " << num2 <<endl;
    // }

// end line = endl;

/*
    cout<< "hello world\n";
    cout<< "hello world" <<endl;
    
    int a = 10;
    char ch = 'w';
    cout<< "ch = " << ch <<endl;
    cout<< "a = " << a <<endl;
*/


/*
    int num = 0;
    char ch = '0';
    cin>>num>>ch;
    cout<< "num = " << num <<endl;
    cout<< "ch = " << ch <<endl;
*/

// 缺省参数
// 半缺省只能是从右往左
// 参数连续串
// 缺省参数也叫默认参数
// 默认参数可以不传，不是默认参数的必须传参数

/*
    Func();
    Func(2);
*/

// 函数重载
// 函数名修饰规则
// 参数个数，类型，顺序
// 返回值没有要求的,返回值不构成重载
/*
    cout<< add(2, 4) <<endl;
    cout<< add(2, 4, 4) <<endl;
    cout<< add(2, 4, 4.2) <<endl;
*/

// 函数重载更深的理解：函数名修饰规则。
// 什么是函数重载
// c++是如何支持函数重载的，为什么c语言不支持。
// g++ -c test.cpp -o test.o
// nm test.o
//  

// 引用
// 引用语法
// 类型& 别名 = 变量名

    /* int a = 55; */
    /* int& ra = a; */
    /* cout<< ra <<endl; */

    /* ra = 55; */

    /* cout<< ra <<endl; */
    /* cout<< a  <<endl; */
    /* cout<< &a <<endl; */
    /* cout<< &ra <<endl; */

// 引用定义的时候初始化
// 一个变量多个引用
// 一个引用绑定了一个实体就不能切换

/* 权限只能缩小，不能方法 */

    const int a = 0;
    const int& b = a;

    int c = 55;
    int& d = c;
    const int& e = c;

    const int f = 99;
    const int& h = f;

/* 临时变量具有常属性 */
/* 隐士类型转换 */
    int i = 66;
    const double& di = i;

    return 0;
}

