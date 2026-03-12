#include <iostream>
#include <cassert>
#include <cstring>
using std::swap;
using std::cout;
using std::endl;

class string 
{
public:
  string(const char* str = "nullptr")
    :_str(nullptr)
    ,_size(0)
    ,_capacity(0)
    {
      if(str == nullptr)
      {
        str = "";
      }

      _size = strlen(str);                // 不会计算\0的
      _capacity = _size;
      _str = new char[_capacity + 1];  // 多开一个存储\0
      memcpy(_str, str, _size + 1);    // \0一并拷贝过去的
    }
  string(const string& s)
    :_str(new char[s._capacity + 1])
    ,_size(s._size)
    ,_capacity(s._capacity)
  {
    memcpy(_str, s._str, _size + 1);
  }
  
  string& operator=(string s)
  {
      Swap(s);
      return *this;
  }
  
  ~string()
  {
    delete[] _str;
    _str = nullptr;
    _size = _capacity = 0;
  }

private:
  void Swap(string& s)
  {
    swap(_str, s._str);
    swap(_size, s._size);
    swap(_capacity, s._capacity);
  }

public:
  using iterator=char*;
  using const_iterator = const char*;
  static const size_t npos;
  
  iterator begin()
  {
    return _str;
  }
  
  iterator end()
  {
    return _str + _size; // 有效数据的下一个位置
  }

  const_iterator begin() const 
  {
    return _str;
  }

  const_iterator end() const 
  {
    return _str + _size;
  }



public:
  size_t size() const
  {
    return _size;
  }

  size_t capacity() const 
  {
    return _capacity;
  }

  bool empty() const 
  {
    return _size == 0;
  }

  const char* c_str() const // 者必须返回cons char*, 因为你传出去了，指针就会破坏这个对象的 
  {
    return _str;
  }

public:
  char& operator[](size_t i)
  {
    assert(i < _size);
    return _str[i];
  }

  const char& operator[](size_t i) const
  {
    assert(i < _size);
    return _str[i];
  }

public:
  void clear()
  {
    _size = 0;
    _str[0] = '\0';
  }
  
  void  reserve(size_t n )
  {
    if(n <= _capacity)
    {
      return;
    }
    
    char* tmp = new char[n + 1];
    memcpy(tmp, _str, _size + 1);

    delete[] _str;
    _str = tmp;
    _capacity = n;
  }
  
  void resize(size_t n, char ch = '\0')
  {
    if(n < _size)
    {
      _size = n;
      _str[_size] = '\0';
    }

    if(n > _capacity)
    {
      reserve(n);
    }
    
    for(size_t i = _size; i < n; ++i)
    {
      _str[i] = ch;
    }
    
    _size = n;
    _str[n] = '\0';
  }

public:
  void push_back(char ch)
  {
    if(_size == _capacity)
    {
      size_t newCapacity = (_capacity == 0 ? 2 : _capacity * 2);
      reserve(newCapacity);
    }
    
    _str[_size++] = ch;
    _str[_size] = '\0';
  }

  /*
   *void pop_back()
   *{
   *  assert(_size > 0);
   *  --_size;
   *  _str[_size] = '\0';
   *}
   */
  
  void append(const char* str)
  {
    assert(str);
    size_t len = strlen(str);
    if(_size + len > _capacity)
    {
      reserve(_size + len);
    }

    memcpy(_str + _size, str, len + 1); // 从_size开始拷贝len个数据，然后呢+1就是\0的。
    _size += len;
  }

  string& insert(size_t pos, char ch)
  {
    assert(pos <= _size);
    if(_size == _capacity)
    {
      size_t newCapacity = (_capacity == 0 ? 2 : _capacity * 2);
      reserve(newCapacity);
    }
  
    // 把 A 区域的数据复制到 B 区域，要求 A 和 B 不打架
    // 在同一块内存里搬家，哪怕前后区域压在一起，也能安全搬
    // _str + pos + 1
    memmove(_str + pos + 1, _str + pos, _size - pos + 1);
    _str[pos] = ch;
    ++_size;
    
    return *this;
  }

  string& insert(size_t pos, const char* str)
  {
    assert(pos <= _size);
    assert(str);

    size_t len = strlen(str);
    if(_size + len > _capacity)
    {
      reserve(_size + len);
    }

    memmove(_str + pos + len, _str + pos, _size - pos + 1);
    memcpy(_str + pos, str, len);
    _size += len;

    return *this;
  }

  string& erase(size_t pos, size_t len = npos)
  {
    assert(pos <= _size);
    if(pos == _size)
    {
      return *this;
    }

    if(len == npos || pos + len >= _size)
    {
      _size = pos;
      _str[_size] = '\0';
      return *this;
    }

    std::memmove(_str + pos, _str + pos + len, _size - pos -len + 1);
    return *this;
  }

public:
  size_t find(char ch, size_t pos = 0) const 
  {
    if(pos >= _size)
    {
      return npos;
    }

    for(size_t i = pos; i < _size; i++)
    {
      if(_str[i] == ch)
      {
        return i;
      }
    }
    
    return npos;
  }

  size_t find(const char* str, size_t pos = 0) const 
  {
    assert(str);
    if(pos > _size)
    {
      return npos;
    }

    const char* p = strstr(_str + pos, str);
    if(p == nullptr)
    {
      return npos;
    }

    return p -_str;
  }

private:
  char* _str;
  size_t _size;
  size_t _capacity;
};
const size_t string::npos = -1;

void test1()
{
  string s1;
  string s2(s1);
  string s3("adcdfe");

  s1 = s3;
  for(auto e : s3)
  {
    cout<< e; // 这里为什么不需要*呢？
  }
  cout<<endl;

}

int main()
{
  test1();

  




  return 0;
}
