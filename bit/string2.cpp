#include <iostream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <utility>
using namespace std;
namespace lic
{
class string 
{
  friend std::ostream& operator<<(std::ostream& out, const string& s);
  friend std::istream& operator>>(std::ostream& in, const string& s);

public:
  using iterator = char*;   // 重新去一个名字给char*
  using const_iterator = const char*;
  static const size_t npos;

public:
  string(const char* str = "")
    :_str(nullptr)
    ,_size(0)
    ,_capacity(0)
    {
      if(str == nullptr)
      {
        str = "";
      }
      
      _size = std::strlen(str);     // strlen不会计算\0
      _capacity = _size;
      _str = new char[_capacity + 1];
      std::memcpy(_str, str, _size+1);
    }
  
  string(const string& other)
    :_str(new char[other._capacity + 1])
    ,_size(other._size)
    ,_capacity(other._capacity)
  {
    std::memcpy(_str, other._str, _size+1);
  }

  string& operator=(string other) // 注意这是传值，临时数据。copy_swap
  {
    swap(other);
    return *this;
  }

  ~string()
  {
    delete[] _str;
    _str = nullptr;
    _size = _capacity = 0;
  }

private:
  void swap(string& other)
  {
    std::swap(_str, other._str);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
  }

public:
  iterator begin()
  {
    return _str;
  }

  iterator end()
  {
    return _str + _size;
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

  const char* c_str() const 
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
  
  void reserve(size_t n)
  {
    if(n <= _capacity)
    {
      return;
    }

    char* newStr = new char[n + 1];
    std::memcpy(newStr, _str, _size + 1); // 加一就是为了拷贝\0;

    delete[] _str;
    _str = newStr;
    _capacity = n;
  }
  
  void resize(size_t n, char ch = '\0')
  {
    if(n < _size)
    {
      _size = n;
      _str[_size] = '\0';
      return ;
    }

    if(n > _capacity)
    {
      reserve(n);
    }

    for(size_t i = _size; i < n; i++)
    {
      _str[i] = ch;
    }

    _size = n;
    _str[_size] = '\0';
  }
  
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

  void append(const char* str)
  {
    assert(str);
    size_t len = strlen(str);
    if(_size + len > _capacity)
    {
      reserve(_size + len);
    }

    std::memcpy(_str + _size, str, len+1);
    _size += len;
  }

  string& operator+=(char ch)
  {
    this->push_back(ch);
    return *this;
  }
  
  string& operator+=(const char* str)
  {
    this->append(str);
    return *this;
  }

  string& insert(size_t pos, char ch)
  {
    assert(pos <= _size);
    if(_size == _capacity)
    {
      size_t newCapacity = (_capacity == 0 ? 2 : _capacity * 2);
      reserve(newCapacity);
    }
    
    std::memmove(_str + pos + 1, _str + pos, _size - pos + 1); // _size - pos有效元素， +1字符\0
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
    
    std::memmove(_str + pos + len, _str + pos, _size - pos + 1);
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

  size_t find(const char* str, size_t pos) const 
  {
    assert(str);
    if(pos > _size)
    {
      return npos;
    }
    
    const char* p = std::strstr(_str + pos, str);
    if(p == nullptr)
    {
      return npos;
    }

    return p - _str;
  }

public:
  bool operator<(const  string& other) const 
  {
    return std::strcmp(_str, other._str) < 0;
  }

  bool operator==(const  string& other) const 
  {
    return std::strcmp(_str, other._str) == 0;
  }

  bool operator!=(const  string& other) const 
  {
    return !(*this == other);
  }

  bool operator<=(const  string& other) const 
  {
    return *this < other || *this == other;
  }

  bool operator>(const  string& other) const 
  {
    return !(*this <= other);
  }

  bool operator>=(const string& other) const 
  {
    return !(*this < other);
  }

private:
  char* _str;
  size_t _size;
  size_t _capacity;
};

const size_t string::npos = static_cast<size_t>(-1);
std::ostream& operator<<(std::ostream& out, const string& s)
{
  return out<<s.c_str();
}


std::istream& operator>>(std::istream& in, string& s)
{
    s.clear();

    char ch = 0;

    while (in.get(ch) && std::isspace(static_cast<unsigned char>(ch)))
    {
    }

    if (!in)
    {
        return in;
    }

    do
    {
        if (std::isspace(static_cast<unsigned char>(ch)))
        {
            break;
        }

        s += ch;
    } while (in.get(ch));

    return in;
}

}

void test1()
{
    lic::string s("lichermionex");
    std::cout<< s.size() <<std::endl;
    std::cout<< s.capacity() <<std::endl;
    std::cout<< s.c_str() <<std::endl;
    for(size_t i = 0; i < s.size(); i++)
    {
      cout<<s[i];
    }
    cout<<endl;
}


int main()
{
  test1();

}
