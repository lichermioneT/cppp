#include <iostream>
#include <list>
#include <vector>
#include <deque>
using namespace std;



template<class T, class Container>
class stack 
{
public:
  void push(const T& x)
  {
    _con.push_back(x);
  }
  
  void pop()
  {
    _con.pop_back();
  }

  size_t size() const 
  {
    return _con.size();
  }

  bool empty() const 
  {
    return _con.empty();
  }

  T& top()
  {
    return _con.back();
  }

private:
  Container _con;
};


template<class T, class Container>
class queue
{
public:
  void push(const T& x)
  {
    _con.push_back(x);
  }
  
  void pop()
  {
    _con.pop_front(); 
  }

  size_t size() const 
  {
    return _con.size();
  }

  bool empty() const 
  {
    return _con.empty();
  }

  T& front()
  {
    return _con.front();
  }
  
  T& back()
  {
    return _con.back();
  }

private:
  Container _con;
};


void test4()
{
  deque<int> d;
  d.push_back(1);
  d.push_back(2);
  d.push_back(3);
  d.push_back(4);
  d.push_back(5);

  d.push_front(9);
  d.push_front(8);
  d.push_front(7);
  d.push_front(6);
  d.push_front(0);

  for(auto& e : d )
  {
    cout<< e << " ";
  }
  cout<<endl;
}


int main()
{
// 容器适配器的
// stl的stack和queue是通过容器适配转换出来的，不是原生实现的，为什么呢》？ 复用呢
// c++是一个极度关注效率的语言
// 导致因为一丁点效率变的扭曲
// 比如：类型萃取
 /*
  *test3();
  */

//deque双关队列 既有list的优点和vector的优点呢
//operator[]
//支持push_back,push_front
//支持pop_back, pop_front
//deque缺点呢
  test4(); // 随机访问的效率不如vector

// stack和queue没有涉及到它的随机访问呢。
// stack和queue只是设计头和尾的操作呢。
// stack和queue没有迭代器，因为只需要在头部和尾部进行操作呢

//deque
//头插尾插数据满了直接开辟新的空间,不扩容的
//中控映射的方式[指针数据的方式]
//operator[]：计算在那个指针指向的位置呢。
//迭代器相当的复杂，四个指针，

  return 0;
}

/*
 *void test1()
 *{
 *  stack<int> st; // 想象成一个直放的数组，只能从放数据的地方出来的。
 *  st.push(1);
 *  st.push(2);
 *  st.push(3);
 *  st.push(4);
 *  st.push(5);
 *
 *  // 如果栈是空的，返回 true
 *  // 如果栈不是空的，返回 false
 *  while(!st.empty())
 *  {
 *    cout<< st.top() << " ";
 *    st.pop();
 *  }
 *  cout<<endl;
 *}
 *
 */

void test2()
{
  /*
   *stack<int, vector<int>> st; // 想象成一个直放的数组，只能从放数据的地方出来的。
   */

  stack<int, list<int>> st; // 想象成一个直放的数组，只能从放数据的地方出来的。
  st.push(1);
  st.push(2);
  st.push(3);
  st.push(4);
  st.push(5);

  // 如果栈是空的，返回 true
  // 如果栈不是空的，返回 false
  while(!st.empty())
  {
    cout<< st.top() << " ";
    st.pop();
  }
  cout<<endl;
}

void test3()
{
  // 不能用vector，因为没有pop_front;
  /*
   *queue<int, vector<int>> q;  insert或者erase也可以的，效率不高呢的。听劝吧
   */


  queue<int, list<int>> q;
  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);
  q.push(5);

  while(!q.empty())
  {
    cout<<q.front() << " ";
    q.pop();
  }
  cout<<endl;
}
