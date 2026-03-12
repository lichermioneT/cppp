#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

//仿函数，对象重载()了的
//优先级队列，底层通过仿函数，进行控制大小堆，实现的
template<class T>
struct Less 
{
  bool operator()(const T& x1, const T& x2)
  {
    return x1 < x2;
  }
};

template<class T>
struct Greater
{
  bool operator()(const T& x1, const T& x2)
  {
    return x1 > x2;
  }
};

template<class T, class Container = vector<T>, class Compare = less<T>>
class priority_queue 
{
private:
  void adJustUp(int child)
  {
   int parent = (child - 1)/2;
   Compare com;
   while(child > 0)
   {
     //if(_con[child] > _con[parent])
     if(com(_con[parent], _con[child]))
     {
       swap(_con[parent], _con[child]);
       child = parent;
       parent = (child - 1) / 2;
     }
     else 
     {
       break;
     }
   }
  }
  void  adJustDown(int root)
  {
    Compare com;
    int parent = root;
    int child = parent * 2 + 1;
    while(child < _con.size())
    {
      /*
       *if(child + 1 < _con.size() && _con[child + 1] > _con[child])
       */
      if(child + 1 < _con.size() && com(_con[child], _con[child + 1]))
      {
        ++child;
      }

      /*
       *if(_con[child] > _con[parent])
       */
      if(com(_con[parent], _con[child]))
      {
        swap(_con[child], _con[parent]);
        parent = child;
        child  = parent * 2 + 1;
      }
      else 
      {
        break;
      }
    }
  }
public:
  void push(const T& x) // 向上调整算法
  {
    _con.push_back(x);
    adJustUp(_con.size() - 1);
  }

  void pop()
  {
    swap(_con[0], _con[_con.size() - 1]);
    _con.pop_back();
    adJustDown(0);
  }

  T& top()
  {
    return _con[0];
  }

  size_t size() const 
  {
    return _con.size();
  }

  bool empty() const 
  {
    return _con.empty();
  }
private:
  Container _con;
};

void test1()
{
  priority_queue<int> pq;
  pq.push(1);
  pq.push(3);
  pq.push(9);
  pq.push(5);
  pq.push(7);
  pq.push(4);
  pq.push(6);
  pq.push(1);
  pq.push(0);
  while(!pq.empty())
  {
    cout<< pq.top() << " ";
    pq.pop();
  }
  cout<<endl;
}

//处了默认访问 限定符不一样，struct和class在c++中是一样的
//全部公用struct, 私有公用class
//仿函数,实际上是重载了(),它的对象可以向函数一样去使用的。

// 不要意思c++这里写错了的

// vector<int> v
// sort()排序
// sort(v.begin(), v.end())
// greater
// sort(v.begin(), v.end(), less<)


void test3()
{
  vector<int> v;
  v.push_back(1);
  v.push_back(3);
  v.push_back(5);
  v.push_back(34);
  v.push_back(98);
  v.push_back(33);
  v.push_back(34);
  sort(v.begin(), v.end());
  for(auto e : v)
  {
    cout<<e << " ";
  }
  cout<<endl; 
  sort(v.begin(), v.end(), greater<int>());
  for(auto e : v)
  {
    cout<<e << " ";
  }
  cout<<endl; 
}


// 容器：string/vector/list/deque 
// 适配器：stack/queue/priority_queue 
// 迭代器：iterator const_iterator r cr 
// 算法： find,sort,reverse
// 仿函数：less/greater
// STL源码解析

int main()
{

// deque数组指针开始从中间插入数据的
// 迭代器四个指针
// 1.operator[] 效率低
// 2.迭代器遍历相对复杂，效率也有影响的

// vector优点 头插头删效率低，增容代价大
// list不支持随机访问的。
// deque的优点
// T* [N] 数组指针


// 优先级队列
// 优先级高的数据先进行出去的
// priority_queue
// 它的适配器就是vector

// 适配出来的容器，一般都不支持迭代器遍历，因为通常包含了一些特殊性质的

// 堆
// 完全二叉树
// 需要和下标完全结合在一起的
//   
  /*
   *test1();
   *Less<int> lessfunc;
   *cout<< lessfunc(1, 2) <<endl;
   *cout<< lessfunc.operator()(100, 2) <<endl;
   */
  test3();

  return 0;
}

void test()
{
// 默认是大堆数据结构实现的
  // 想实现小的优先级高呢，仿函数登场
/*
 * priority_queue<int> pq;
 * pq.push(11);
 * pq.push(12);
 * pq.push(13);
 * pq.push(14);
 * pq.push(15);
 *  
 * while(!pq.empty())
 * {
 *   cout<< pq.top() << " ";
 *   pq.pop();
 * }
 * cout<<endl;
 *
 * priority_queue<int, vector<int>, greater<int>> pq2; // 仿函数登场呢
 * pq2.push(5);
 * pq2.push(4);
 * pq2.push(3);
 * pq2.push(2);
 * pq2.push(1);
 *
 * while(!pq2.empty())
 * {
 *   cout<< pq2.top() << " ";
 *   pq2.pop();
 * }
 * cout<<endl;
 */
}
