#include <iostream>
using namespace std;

template<class T>
struct __list_node 
{
  __list_node(const T& x)
      :_next(nullptr)
      ,_prev(nullptr)
      ,_data(x)
  {}
  __list_node<T>* _next;
  __list_node<T>* _prev;
  T _data;
};

template<class T>
struct __list_iterator
{
  typedef __list_iterator<T> node;
  node* _node;

  __list_iterator(node* x)
      :_node(x)
  {}

  T& operator*()
  {
    return _node->_data;
  }

  __list_iterator<T>& operator++()
  {
    _node = _node->_node;
    return _node;
  }

};

template<class T>
class list 
{
typedef __list_node<T> node;
public:
// 代头双向循环链表的
  list()
  {
    _head = new node;
    _head->_next = _head;
    _head->_preva = _head;
  }

  void push_back(const T& x)
  {
      node* newNode = new node(x);
      node* tail = _head->_prev;
// list有没有数据插入都是一样的呢
      tail->_next = newNode;
      newNode->_prev = tail;

      tail->_next = _head;
      _head->_prev = newNode;
  }
private:
  node* _head;
};







int main()
{
// list的迭代器
// 一个类型取封装节点的指针，构成一个自定义类型
// 然后重载* ++等运算符，就可以达到我们的要求的
  list<int> lt1;
  lt1.push_back(1);
  lt1.push_back(2);
  lt1.push_back(3);
  lt1.push_back(4);
  lt1.push_back(5);


  return 0;
}
