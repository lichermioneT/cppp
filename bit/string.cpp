#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

namespace lic 
{
class string 
{
  public:
    string(const char* str = "")
    {
      _size = strlen(str);
      _str = new char[_size + 1];
      _capacity = _size ;
      strcpy(_str, str);
    }
    
    string(const string& that)
    {
      _size = strlen(that._str);
      _str = new char[_size + 1];
      _capacity = _size + 1;
      strcpy(_str, that._str);
    }

    ~string()
    {
      delete[] _str;
      _str = nullptr;
      _size = _capacity = 0;
    }

    
    char* c_str() const 
    {
      return _str;
    }
  private:
    char* _str;
    size_t _size;
    size_t _capacity;
};
}

int main()
{
  using namespace lic;
  string s("aaaaaaaaaaaaa");
  string s1(s);
  
  cout<< s.c_str() <<endl;
  cout<< s1.c_str() <<endl;

















  return 0;
}
