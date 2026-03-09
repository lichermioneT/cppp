#include <iostream>
#include <string>
#include <cassert>
#include <cstring>

template<class T>
class vector 
{
public:
  typedef T* iterator;
  typedef const T* const_iterator;

public:
  vector()
    :_start(nullptr)
    ,_finish(nullptr)
    ,_endofstorage(nullptr)
  {}

/*
 *  vector(const vector<int>& v)
 *  {
 *    _start = new T[v.capacity()];
 *    _finish = _start;
 *    _endofstorage = _start + v.capacity();
 *
 *    for(size_t i = 0; i < v.size(); i++)
 *    {
 *      *_finish = v[i];
 *      ++_finish;
 *    }
 *  }
 */
  
  vector(const vector<int>& v)
    :_start(nullptr)
    ,_finish(nullptr)
    ,_endofstorage(nullptr)
  {
    reserve(v.capacity());
    for(auto& e : v)
    {
      push_back(e);
    }
  }
  
  // v1=v2 
  // v1原来的数据会进行释放的
  vector<T>& operator=(vector<int> v) // 注意这里传入的是临数据的，会进行考核，也会把我们交换的数据进析构的copy_swap写法的
  {
    swap(v);
    return *this;
  }
  
  void swap(vector<T>&  v)
  {
    std::swap(_start, v._start);
    std::swap(_finish, v._finish);
    std::swap(_endofstorage, v._endofstorage);
  }

  ~vector()
  {
    delete[] _start;
    _start = _finish = _endofstorage = nullptr;
  }

  void push_back(const T& x)
  {
/*
 *      if(_finish == _endofstorage)
 *      {
 *        size_t newCapacity = capacity() == 0 ? 2 : capacity() * 2;
 *        reserve(newCapacity);
 *      }
 *
 *     *_finish = x;
 *     ++_finish;
 */

    insert(_finish, x);
  }

  void pop_back()
  {
    /*
     *assert(_start < _finish);
     *--_finish;
     */

    erase(_finish - 1);
  }


// pos失效了的了，增容了
// 细节的呢
  void insert(iterator pos, const T& x)
  {
      assert(pos <= _finish);
      if(_finish == _endofstorage)
      {
        size_t n = pos - _start;
        size_t newCapacity = capacity() == 0 ? 2 : capacity() * 2;
        reserve(newCapacity);
        pos = _start + n;
      }
      
      iterator end = _finish - 1;
      while(end >= pos)
      {
        *(end + 1) = *end;
        end--;
      }

      *pos = x;
      ++_finish;
  }
  

  iterator erase(iterator pos)
  {
    assert(pos < _finish);
  
    iterator it = pos;
    while(it < _finish)
    {
      *it = *(it + 1);
      ++it;
    }
    --_finish;
    return pos;
  }

  void  reserve(size_t n)
  {
    if(n <= capacity())
    {
      return;
    }

    size_t oldSize = size();

    T* tmp = new T[n];
    if(_start)
    {
      for(size_t i = 0; i < oldSize; i++)
      {
        tmp[i] = _start[i];
      }
      delete[] _start;
    }
// memcpy() 这里拷贝有问题的  按字节拷贝的
// delete[] _str  delete[] 调用析构函数的

    _start = tmp;
    _finish = tmp + oldSize;
    _endofstorage = _start + n;
  }

  void resize(size_t n, const T& val = T())
  {
    if(n < size())
    {
      _finish = _start + n;
    }
    else 
    {
      if(n > capacity())
      {
        reserve(n);
      }
      
      while(_finish < _start + n)
      {
        *_finish = val;
        ++_finish;
      }
    }
  }

  T& operator[](size_t i)
  {
    assert(i < size()); 
    return _start[i];
  }

  const T& operator[](size_t i) const
  {
    assert(i < size()); 
    return _start[i];
  }
  size_t size() const 
  {
    return _finish - _start;
  }
  
  size_t capacity() const 
  {
    return _endofstorage - _start;
  }

  iterator begin()
  {
    return _start;
  }

  iterator end()
  {
    return _finish;
  }

  const_iterator begin() const
  {
    return _start;
  }

  const_iterator end() const
  {
    return _finish;
  }
private:
 iterator _start; 
 iterator _finish; 
 iterator _endofstorage;
};

template<class T>
void print_arr(const vector<T>& v)
{
  for(auto& e : v)
  {
    std::cout<<e;
  }
  std::cout<<std::endl;
}



int main()
{

//1.vector缺点，头部和中部的数据插入，需要移动数据
//2.vector缺点，增容的时候空间会浪费时间的

//1.vector优点，支持随机访问，排序，二分查找，堆
//list就是为了解决vector的缺点

//list 支持头插，中间插入
//增加数据，不需要扩容的
//不支持随机访问的
//vector和list相辅相成的两个容器的
  vector<std::string> v;
  v.push_back("111111111111111111111111111111111111111111111111111111111111111111");
  v.push_back("111111111111111111111111111111111111111111111111111111111111111111");
  v.push_back("111111111111111111111111111111111111111111111111111111111111111111");
  v.push_back("111111111111111111111111111111111111111111111111111111111111111111");
  v.push_back("111111111111111111111111111111111111111111111111111111111111111111");
  print_arr(v);

  return 0;
}

void test7()
{
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  print_arr(v);

  vector<int> v2(v);
  v2.push_back(6);
  print_arr(v2);

  vector<int>  v3;
  v3 = v2;
  print_arr(v3);
}


// c++对内置类型进行了，扩展，类似自定义对象的构造函数
// 这里实际上是为了适配模板了
void test6()
{
  int i = int();
  double j = double();
  std::cout<< i <<std::endl;
  std::cout<< j <<std::endl;
}

// memset函数是按照字节进行操作的。慎用的
void memset_f()
{
  int arr[10] = {0};
  memset(arr, 1, sizeof(arr));

  for(auto e: arr)
  {
    std::cout<<e << std::endl; // 16843009
  }
  std::cout<<std::endl;
}

void test5()
{
  vector<int> v;
  v.reserve(10);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  v.push_back(6);
  v.push_back(7);
  for(auto e : v)
  {
    std::cout<< e;
  }
  std::cout<<std::endl;
  std::cout<<std::endl;
  std::cout<< v.size() <<std::endl;
  std::cout<< v.capacity() << std::endl;
  
  v.resize(4);
  for(auto e : v)
  {
    std::cout<< e;
  }
  std::cout<<std::endl;
  std::cout<<std::endl;
  std::cout<< v.size() <<std::endl;
  std::cout<< v.capacity() << std::endl;
  
  v.resize(8);
  for(auto e : v)
  {
    std::cout<< e;
  }
  std::cout<<std::endl;
  std::cout<<std::endl;
  std::cout<< v.size() <<std::endl;
  std::cout<< v.capacity() << std::endl;
  
  v.resize(12);
  for(auto e : v)
  {
    std::cout<< e;
  }
  std::cout<<std::endl;
  std::cout<<std::endl;
  std::cout<< v.size() <<std::endl;
  std::cout<< v.capacity() << std::endl;
}

void test4()
{
  vector<int> v;
  for(size_t i = 0; i < 10; i++)
  {
    v.insert(v.begin(), i);
  }
  
  v.pop_back();
  v.pop_back();
  v.pop_back();

  for(auto e : v)
  {
    std::cout<< e ;
  }
  std::cout<<std::endl;
}

void test3()
{
  vector<int> v;
  for(size_t i = 0; i < 10; i++)
  {
    v.insert(v.begin(), i);
  }
  
  vector<int>::iterator it = v.begin();
  while(it != v.end())
  {
    if(*it % 2 == 0)
    {
      it = v.erase(it);
    }
    else 
    {
      ++it;
    }
  }

  for(auto e : v)
  {
    std::cout<<e;
  }
  std::cout<<std::endl;
}

void test2()
{
  vector<int> v;
  /*
   *v.insert(v.begin(),3);
   */
  v.insert(v.end(), 4);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.insert(v.begin(),3);
  v.insert(v.end(), 4);
  vector<int>::iterator it = v.begin();
  while(it != v.end())
  {
    std::cout<< *it;
    ++it;
  }
  std::cout<<std::endl;
}

// vector的迭代器和遍历方式的
void test()
{
  vector<int> v;
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  
  /*
   *vector<int>::iterator it = v.begin();
   *while(it != v.end())
   *{
   *  std::cout<< *it;
   *  ++it;
   *}
   *std::cout<<std::endl;
   */
  
  /*
   *for(auto e : v)
   *{
   *  std::cout<<e;
   *}
   *std::cout<<std::endl;
   */
    
  /*
   *for(size_t i = 0; i < v.size(); i++)
   *{
   *  std::cout<< v[i];
   *}
   *std::cout<<std::endl;
   */
}
