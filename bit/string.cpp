#include <iostream>
#include <cassert>
#include <cstring>



namespace lic 
{
class string 
{
  friend std::ostream& operator<<(std::ostream& out, const string& s);
public:

/*
 *迭代器
 */
  typedef char* iterator;
  iterator begin()
  {
    return _str; 
  }

  iterator end()
  {
    return _str + _size;
  }


    string(const char* str = "")
      :_str(nullptr)
      ,_size(0)
      ,_capacity(0)
    {
      if(str == nullptr)
      {
        str = "";
      }
      _size = strlen(str);
      _str = new char[_size + 1];
      _capacity = _size ;
      strcpy(_str, str);
    }
    
    string(const string& that)
      :_str(nullptr)
      ,_size(that._size)
      ,_capacity(that._capacity)
    {
      _str = new char[that._capacity + 1];
      strcpy(_str, that._str);
    }

    string& operator=(const string& that)
    {
      if(this != &that)
      {
        char* tmp = new char[strlen(that._str) + 1];
        strcpy(tmp, that._str);
        delete[] _str;

        _str = tmp;
        _size = that._size;
        _capacity = that._capacity;
      }
      return *this;
    }


    ~string()
    {
      delete[] _str;
      _str = nullptr;
      _size = _capacity = 0;
    }

    char& operator[](size_t pos)
    {
      assert(pos < _size);
      return _str[pos];
    }

    const char& operator[](size_t pos) const
    {
      assert(pos < _size);
      return _str[pos];
    }
    
    void reserve(size_t n)
    {
      if(n > _capacity)
      {
          char* tmp = new char[n + 1]; // 多开一个进行存储\0
          strcpy(tmp, _str);
          
          delete[] _str;
          _str = tmp;
          _capacity = n;
      }
    }
    
    void push_back(char ch)
    {
      if(_size == _capacity)
      {
        size_t newCapacity = _capacity == 0 ? 2 : _capacity*2;
        char* newStr = new char[newCapacity + 1];
        strcpy(newStr, _str);
        delete[] _str;

        _str = newStr;
        _capacity = newCapacity;
      }

      _str[_size] = ch;
      _size++;
      _str[_size] = '\0';
    }
    
    void append(const char* str)
    {

    }

    const char* c_str() const 
    {
      return _str;
    }
    
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
      return  _size == 0;
    }
  private:
    char* _str;
    size_t _size;
    size_t _capacity;
};
    std::ostream& operator<<(std::ostream& out, const string& s)
    {
      for(size_t i = 0; i < s.size(); i++)
      {
        out<< s[i];
      }
      return out;
    }
}

int main()
{
  lic::string s("aaaaaaaaaaaaa");
  lic::string s1(s);
  
  std::cout<< s.c_str() <<std::endl;
  std::cout<< s1.c_str() <<std::endl;
   
  s1.push_back('a');
  s1.push_back('c');
  s1.push_back('b');
  s1.push_back('d');
  s1.push_back('f');
  
  /*
   *std::cout<< s1 <<std::endl;
   */
  
  for(auto& e : s1)
  {
    e+=2;
    std::cout<< e;
  }
  std::cout<<std::endl;

  for(size_t i = 0; i < s1.size(); i++)
  {
    s[i] -= 2;
    std::cout<< s1[i];
  }
  std::cout<<std::endl;












  return 0;
}
