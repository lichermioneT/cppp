#include <iostream>
#include <cassert>
#include <cstring>



namespace lic 
{
class string 
{
  friend std::ostream& operator<<(std::ostream& out, const string& s);
  friend std::istream operator>>(std::istream& in, string& s);
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
        _capacity = that._capacity + 1;
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
          char* newStr= new char[n + 1]; // 多开一个进行存储\0
          strcpy(newStr, _str);
          delete[] _str;
          _str = newStr;
          _capacity = n;
      } 
    }
    
    void push_back(char ch)
    {
      if(_size == _capacity)
      {
        size_t newCapacity = _capacity == 0 ? 2 : _capacity*2;
        reserve(newCapacity);
      }

      _str[_size] = ch;
      _size++;
      _str[_size] = '\0';
    }
    
    void append(const char* str)
    {
        size_t len = strlen(str);
       if(_size + len > _capacity) 
       {
         reserve(_size + len);
       }

       strcpy(_str + _size, str);
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
        size_t newCapacity = _capacity == 0 ? 2 : _capacity * 2;
        reserve(newCapacity);
      }
        
      for(size_t i = _size; i > pos; i--)
      {
        _str[i] = _str[i-1];
      }

      _str[pos] = ch;
      ++_size;
      _str[_size] = '\0';
      
      return *this;
    }

    string& insert(size_t pos, const char* str)
    {
      assert(pos <= _size);
      size_t len = strlen(str);
      if(_size + strlen(str) > _capacity)
      {
          reserve(_size + len);
      }
      
      for(size_t i = _size; i > pos; i--)
      {
        _str[i + len - 1] = _str[i - 1];
      }
      
      strncpy(_str+pos, str, len);

      _size += len;

      return *this;
    }

    void resize(size_t n, char ch = '\0')
    {
      if(n < _size)
      {
        _str[n] = '\0';
        _size = n;
      }
      else 
      {
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
    }
    
    void erase(size_t pos, size_t len)
    {
      assert(pos < _size);
       if(pos + len >= _size)
       {
          _str[pos] = '\0';
          _size =  pos;
       }
       else 
       {
         for(size_t i = pos + len; i <= _size; i++)
         {
           _str[i-len] = _str[i];
         }
       }
    }

    size_t find(char ch, size_t pos = 0)
    {
      assert(pos < _size);
      for(size_t i = pos; i < _size; i++)
      {
        if(_str[i] == ch)
        {
          return i;
        }
      }
      return npos;
    }

    size_t find(const char* str, size_t pos)
    {
      assert(pos < _size);
      char* p = strstr(_str, str);
      if(p == nullptr)
      {
        return npos;
      }
      else 
      {
        return p - _str;
      }
    }

    bool operator<(const string& s)
    {
      int ret = strcmp(_str, s._str);
      return ret < 0;
    }

    bool operator==(const string& s)
    {
      int ret = strcmp(_str, s._str);
      return ret == 0;
    }
      
    bool operator<=(const string& s)
    {
      return *this < s || *this == s;
    }

    bool operator>(const string& s)
    {
      return !(*this <= s);
    }

    bool operator>=(const string& s)
    {
      return !(*this < s);
    }

    bool operator!=(const string& s)
    {
      return !(*this == s);
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
    static size_t npos;
};
    std::ostream& operator<<(std::ostream& out, const string& s)
    {
      for(size_t i = 0; i < s.size(); i++)
      {
        out<< s[i];
      }
      return out;
    }
    
    std::istream& operator>>(std::istream& in, string& s)
    {
        while(1)
        {
          char ch;
          ch = in.get();
          if(ch == ' ' || ch == '\0')
          {
            break;
          }
          else 
          {
            s += ch;
          }
        }
        return in;
    }

  size_t string::npos = -1;
}

void test1()
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
    s1[i] -= 2;
    std::cout<< s1[i];
  }
  std::cout<<std::endl;

  s1.append("lichermionex");

  for(size_t i = 0; i < s1.size(); i++)
  {
    std::cout<< s1[i];
  }
  std::cout<<std::endl;

  s1 += 'a';
  s1 += 'b';
  s1 += 'c';
  for(size_t i = 0; i < s1.size(); i++)
  {
    std::cout<< s1[i];
  }
  std::cout<<std::endl;

  s1 += "fadsfasdfs";
  for(size_t i = 0; i < s1.size(); i++)
  {
    std::cout<< s1[i];
  }
  std::cout<<std::endl;

// 字符串数组，结尾\0
// 三部分(\0不算有效字符)
// _str      指针
// _size     已经有多少个字符
// _capacity 能够放多少个字符
  std::cout<< s1.size() << std::endl;
  
  s1.insert(43,'a');
  s1.insert(44,'b');
  s1.insert(45,'c');

  for(size_t i = 0; i < s1.size(); i++)
  {
    std::cout<< s1[i];
  }
  std::cout<<std::endl;

  s1.insert(0, "licherminonn");

  for(size_t i = 0; i < s1.size(); i++)
  {
    std::cout<< s1[i];
  }
  std::cout<<std::endl;

  std::cout<< s1.size() << std::endl;
  s1.insert(58,"asfasdfdsafsdf");

  for(size_t i = 0; i < s1.size(); i++)
  {
    std::cout<< s1[i];
  }
  std::cout<<std::endl;
}

void test2()
{
  lic::string s;
  s.append("afdsssfadfasdf");
  s.erase(1,3);

  for(size_t i = 0; i < s.size(); i++)
  {
    std::cout<< s[i];
  }
  std::cout<<std::endl;

  
}

namespace lic2
{
class string 
{
  public:
  string(const char* str = "")
    :_str(new char[strlen(str) + 1]
    {
      strcpy(_str, str);
    }
  
   // 深拷贝的现代写法
   // 拷贝一个临时对象，然后交换一下。
   string(const string& s)
    :_str(nullptr) // 防止随机值
    {
      string temp(s._str); // 临时对象会析构
      std::swap(_str, temp._str);
    }
    
    sting& operator=(const string& s)
    {
      if(this != &s)
      {
        string temp(s);
        std::swap(_str, temp._str);
      }
      return *this;
    }

  ~string()
  {
    delete[] _str;
    _str = nullptr;
  }

  

private:
  char* _str;
};
}

int main()
{
  test2();
  return 0;
}
