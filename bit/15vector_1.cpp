#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


void test()
{
    vector<int> v; //类型vector<int> v;存的数据就是int类型的
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    
    vector<int> v2(v); // 拷贝构造函数
    
    for(size_t i = 0; i < v.size(); i++)
    {
        cout<< v[i] << " ";  // 运算符重载了的
    }
    cout<<endl;

    vector<int> v3;
    v3.push_back(4);
    v3.push_back(5);
    v3.push_back(6);
    v3.push_back(7);
    v3.push_back(4);

    v = v3;
    for(size_t i = 0; i < v3.size(); i++)
    {
        cout<< v3[i] << " ";
    }
    cout<<endl;
}


void test2()
{
    vector<int> v = {1,2,4,5,7,6,7,5,41,22,23,33,1};
    
    cout<< 1 <<endl;
    for(size_t i = 0; i < v.size(); i++)
    {
        cout<< v[i] << "  ";
    }
    cout<<endl;

    cout<< 2 <<endl;
    vector<int>::iterator it = v.begin(); // 迭代器需要突破类域，才行了的。

    for(size_t i = 0; i < v.size(); i++)
    {
        cout<< *it << "  ";
        it++;
    }
    cout<<endl;


// 范围for本质是迭代器
    cout<< 3 <<endl;
    for(auto e : v)
    {
        cout<< e <<"  ";
    }
    cout<<endl;
}

// 迭代器的正反
// 迭代器的const
// iterator 
// const_iterator 
// reverse_iterator 
// const_reverse_iterator
void test3()
{
    vector<int> v = {1,22,33,44,77,66,44,22,22,5551,11,656};

    vector<int>::iterator it = v.begin();
    while(it != v.end())
    {   
        cout<< *it << "  ";
        it++;
    }
    cout<<endl;

    vector<int>::const_iterator itc = v.cbegin();
    while(itc != v.cend())
    {
        // *cit += 1;
        cout<< *itc << "  ";
        itc++;
    }
    cout<<endl;


    vector<int>::reverse_iterator itr = v.rbegin();
    while(itr != v.rend())
    {
        cout<< *itr << "  ";
        itr++;
    }
    cout<<endl;
}

// vector的扩容机制
// 是一种选择，几倍扩容，根据编译的选择。
// 1.5可能需要频繁扩容
// 2可能浪费跟大的空间的
void test4()
{
    vector<int> v = {1,2,5,6,4,88,5,5111,222222,55,211};
    cout<< v.size() <<endl;
    cout<< v.capacity() <<endl;

    for(size_t i = 0; i < 100; i++)
    {
        v.push_back(i);
        if(v.size() == v.capacity())
        {
            cout<< v.size() <<endl;
        }
    }
    
    cout<< v.size() <<endl;
    cout<< v.capacity() <<endl;
}

// vector的[]    不会检查边界的
// vector的 v.at(); 抛异常
void test5()
{

    vector<int> v = {1,2,3,4,5};
    v[1];
    v.at(1);
}


// 
// 注意vector插入数据只能是传入迭代器
// erase也只能传入迭代器的
// insert和erase可以直接传入迭代器，迭代器可以进行加减的
void test6()
{

    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    v.insert(v.begin(), 0);
    for(auto e: v)
    {
        cout<< e << " ";
    }
    cout<<endl;


    v.insert(v.begin(), -1);

    for(auto e: v)
    {
        cout<< e << " ";
    }
    cout<<endl;
    

}


void test7()
{
    vector<int> v = {11111,7777,555,66,1,2,3,4,5,6,7,8,8,855};
    v.erase(v.begin()); 
    for(auto e : v)
    {
        cout<< e << " ";
    }
    cout<<endl;
    
    auto it =  find(v.begin(), v.end(), 7); // 实际上是一个函数模版
                                            // [first , last)
                                            // 迭代器基本的都是左闭右开
    cout<< *it <<endl;
    sort(v.begin(), v.end());

    for(auto e : v)
    {
        cout<< e << "  ";
    }
    cout<<endl;
}

// vector没有查找函数
// vector<int>::iterator find(v.begin(), v.end(), target);
// find函数，返回目标值的迭代器位置的
// STL区间都是左闭右开的
//
// leetcode136, 137题目的
// 异或

int main()
{
  test();
 /*
  *  test2();
  *  test3();
  *  test4();
  *  test5();
  *  test6();
  *
  *   test7();
  */
    return 0;
}

