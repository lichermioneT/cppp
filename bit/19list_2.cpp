#include <iostream>
#include <cassert>
using namespace std;

// list的node信息
template<class T>
struct __list_node 
{
  __list_node(const T& x = T()) // 这里会让内置类型初始化为零的
      :_next(nullptr)
      ,_prev(nullptr)
      ,_data(x)
  {}

  __list_node<T>* _next;
  __list_node<T>* _prev;
  T _data;
};

// list的iterator信息
// iterator封装了node的使用方法了的
template<class T, class Ref, class Ptr>
struct __list_iterator
{
  typedef __list_iterator<T, Ref, Ptr> Self;
  typedef __list_node<T> Node; 
  Node* _node;

  __list_iterator(Node* node)
      :_node(node)
  {}
  
  //*it 可以读可以写
  Ref& operator*()
  {
    return _node->_data;
  }

  Ptr operator->()
  {
    return &_node->_data;
  }
 Self& operator++() // 这是前置++
  {
    _node = _node->_next;
    return *this;
  }

 Self operator++(int) 
 {
   Self tmp(*this);
   // _node = _node->_next;
   ++(*this);
    return tmp;
 }

 Self& operator--()
 {
   _node = _node->_prev;
   return *this;
 }

 Self operator--(int)
 {
   Self tmp(*this);
   // _node = _node->_prev;
   --(*this);
   return tmp;
 }

 bool operator!=(const Self& it) const
 {
   return _node != it._node;
 }

 bool operator==(const Self& it) const
 {
   return _node == it._node;
 }
};

template<class T>
class list 
{
typedef __list_node<T> Node;
public:
  typedef __list_iterator<T, T&, T*> iterator;
  typedef __list_iterator<T, const T&, const T*> const_iterator;

// 这里构造函数重载，是因为隐含的this指针
// list* const this
// const list* const this  
// 参数的类型不一样的
  iterator begin()
  {
    return iterator(_head->_next);
  }
  
  iterator end()
  {
    return iterator(_head);  // 注意这里的end是_head
  }

  const_iterator begin() const 
  {
    return const_iterator(_head->_next);
  }

  const_iterator end() const 
  {
    return const_iterator(_head);
  }

// 代头双向循环链表的
  list()
  {
    _head = new Node;
    _head->_next = _head;
    _head->_prev = _head;
  }

  list(const list<T>& lt)
  {
    // 注意这里同样也是深拷贝的
    _head = new Node;
    _head->_next = _head;
    _head->_prev = _head;
    
    /*
     *const_iterator it = lt.begin();
     *while(it != lt.end())
     *{
     *  push_back(*it);
     *  ++it;
     *}
     */
  
    for(auto e : lt)
    {
      push_back(e);
    }
  }

/*
 *  list<T>& operator=(list<T>& lt)
 *  {
 *    
 *    if(this != &lt)
 *    {
 *      clear();
 *
 *      for(auto e : lt)
 *      {
 *        push_back(e);
 *      }
 *    }
 *
 *    return *this;
 *  }
 */

  list<T>& operator=(list<int> it) // 这里是传值拷贝数据的。
  {
    swap(_head, it._head); // 头结点给一个临时对象的。
    return *this;
  }

  ~list()
  {
    clear();
    delete _head;
    _head = nullptr;
  }

  void clear()
  {
    iterator it = begin();
    while(it != end())
    {
      erase(it++);
    }
  }

  void push_back(const T& x)
  {
// list有没有数据插入都是一样的呢
/*
 *      Node* newNode = new Node(x);
 *      Node* tail = _head->_prev;
 *      tail->_next = newNode;
 *      newNode->_prev = tail;
 *
 *      newNode->_next = _head;
 *      _head->_prev = newNode;
 */
    insert(end(), x); // 需要理解
  }
  
  void pop_back()
  {
    erase(end());
  }

  void push_front(const T& x)
  {
    insert(begin(), x);
  }
  
  void pop_front()
  {
    erase(begin());
  }
  
  void insert(iterator pos, const T& x)
  {
    Node* cur = pos._node; 
    Node* prev = cur->_prev;

    Node* newNode = new Node(x);
  
    // prev newNode cur
    prev->_next = newNode;
    newNode->_prev = prev;

    newNode->_next = cur;
    cur->_prev = newNode;
  }

  void erase(iterator pos)
  {
    assert(pos != end());
    Node* cur = pos._node;
    Node* prev = cur->_prev;
    Node* next = cur->_next;

    delete cur;

    prev->_next = next;
    next->_prev = prev;
  }

private:
  Node* _head;
};

void print_list(const list<int>& lt)
{
  /*
   *for(auto& e: lt)
   *{
   *  cout<< e << " ";
   *}
   *cout<<endl;
   */


  list<int>::const_iterator it = lt.begin();
  while(it != lt.end())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

void test3()
{
  list<int> lt1;
  lt1.push_back(1);
  lt1.push_back(2);
  lt1.push_back(3);
  lt1.push_back(4);
  lt1.push_back(5);
  lt1.push_front(3333);
  lt1.push_front(1);
  lt1.push_front(2);
  lt1.push_front(3);
  lt1.push_front(4);
  lt1.push_front(5);

  list<int> lt2(lt1);
  print_list(lt2);

  list<int> lt3;

  lt3 = lt1;

  print_list(lt3);
}


// 1.vector和list的区别
//  vector动态增长的数组，随机访问，operator[] 支持排序，二分查找，堆的算法
//  头部或者中间数据插入效率比较低下的 + 增容的代价比较大的
//  list是一个代头的的双向循环链表,任意位置，插入，删除效率on(1);
//  缺点是不支持随机访问的
//  vector和list是一个相辅相成，互补的一个容器的
// 2.vector和list的底层实现
// 3.vector如何增容
// 4.什么是迭代器失效


int main()
{
// list的迭代器
// 一个类型取封装节点的指针，构成一个自定义类型
// 然后重载* ++等运算符，就可以达到我们的要求的
// 头文件的展开了，顺序注意一哈的

// list迭代器失效
// _head 1 2 3 4 5
// lt.erase(it) //3位置的空间已经被释放了，你不能够进行访问的
// 所以erase是返回迭代器的下一个位置的
// insert() 


// insert 插入新元素的位置
// erase  被删除元素的下一个位置
 test3(); 

  return 0;
}

void test()
{
  list<int> lt1;
  lt1.push_back(1);
  lt1.push_back(2);
  lt1.push_back(3);
  lt1.push_back(4);
  lt1.push_back(5);
  list<int>::iterator it = lt1.begin();
  while(it != lt1.end())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

void test2()
{
  struct Date 
  {
    int year = 1;
    int month = 1;
    int day = 1;
  };
  
  list<Date> lt1;
  lt1.push_back(Date());
  lt1.push_back(Date());
  list<Date>::iterator it = lt1.begin();

  while(it != lt1.end())
  {
    /*
     *cout<< *it << " ";   //  注意自定义类型你没有重载输出的  这里迭代器是为了 模拟指针的行为的 
     */
          // it.operator->() 
    cout<< it->year << " " << it->month << " "<< it->month <<endl;
    ++it;
  }

  cout<<endl;
}
