#include <iostream>
#include <cstring>
#include <cassert>
namespace lic
{
class string
{
public:
    string()
        : _str(new char[1])
    {
        _str[0] = '\0'; // 注意\0的存在
    }

    string(const char* str)
    {   
        // 1.
        // 开辟一块新空间,然后把数据拷贝过去的，不然常量字符串，不允许修改的。
        // strlen会计算到\0,不计算\0
        _str = new char[strlen(str) + 1]; // 这里就是在堆里面开辟一块空间的。
        
        // 2.
        // 数据拷贝过去
        strcpy(_str, str); // str(目标地址，源地址) 这里会拷贝\0的,细节拷贝\0的。
    }
    
    /*
     *上面的两个合并成一个全缺省的构造函数
     *string(const char* str = "")
     *  :_str(new char[strlen(str) + 1])
     *{
     *  strcpy(_str, str);
     *}
     */
      
    ~string()
    {
      delete[] _str;
      _str = nullptr;
    }

// 浅拷贝(值拷贝)，只需要把对象的成员属性拷贝给另一个就行的。
// 这里可能析构两次了，这里string的成员属性有指针存在的。
    string(const string& that)
    {
        // 深拷贝
        if (that._str) 
        {
            _str = new char[strlen(that._str) + 1];// 开空间
            strcpy(_str, that._str);               // 拷贝过去了
        }   
        else 
        {
            _str = new char[1];
            _str[0] = '\0';
         }
    }

// 赋值也是一样的，不给的话也是值拷贝的了。
    string& operator=(const string& that)
    {
        // 1. 自赋值检查
        if (this == &that)
            return *this;

        // 2. 释放原内存
        delete[] _str;

        // 3. 分配新内存并拷贝
        if (that._str) 
        {
            _str = new char[strlen(that._str) + 1];
            strcpy(_str, that._str);
         } 
        else 
        {
            _str = new char[1];
            _str[0] = '\0';
        }
        return *this;
    }

    string& operator+=(const char* str)
    {
         if (str == nullptr)
            return *this;

        size_t oldLen = strlen(_str);
        size_t addLen = strlen(str);
    
         // 分配新空间：原来的长度 + 新加的长度 + 1（结尾 \0）
         char* newStr = new char[oldLen + addLen + 1];

         // 拷贝原来的字符串
         strcpy(newStr, _str);

         // 追加新字符串
         strcat(newStr, str);

        // 释放旧内存
        delete[] _str;

        // 更新 _str
        _str = newStr;

        return *this;
    }

    char& operator[](size_t i)
    {
        return _str[i];
    }
    
    char* c_str() const
    {
      return _str;
    }

    size_t size() const
    {
        return strlen(_str);
    }


    void print() const
    {
        std::cout << _str << std::endl;
    }

private:
    char* _str;
};
}

void test()
{
    using namespace lic;
    string s1;
    string s2("lichermionex"); // 这里的lichermionex是字符串常量，不能进行修改的
                               // 字符串字面量

    for(int i = 0; i < s2.size(); i++)
    {
        std::cout<< s2[i] <<std::endl;
    }
    
    std::cout<<std::endl;

    for(int i = 0; i < s2.size(); i++)
    {
        s2[i] += 1;
        std::cout<< s2[i] <<std::endl;
    }

    string s3(s2);
    
    std::cout<< " s3 " <<std::endl;
    for(int i = 0; i < s3.size(); i++)
    {   
        std::cout<< s3[i] <<std::endl;
    }

}

namespace lic2
{

// string对象中存储指针，指针指向的数组存放字符，字符保留\0
class string
{
public:
    string()
        :_str(new char[1])
    {
        _str[0] = '\0';
    }
    
    string(const char* str)
        :_str(new char[strlen(str) + 1]) // 尽量使用new开辟空间了
    {
        strcpy(_str, str);
    }

    //推荐全缺省的构造函数
    //string(const char* str = "")
    //  :_str(new char[strlen(str) + 1])
    //  {
    //      strcpy(_str, str);
    //  }

    ~string()
    {
        delete[] _str;
        _str = nullptr;
    }

    size_t size()
    {
        return strlen(_str);
    }

    char& operator[](size_t i)
    {
        return _str[i];
    }

    string(const string& that)
        :_str(new char[strlen(that._str) + 1])
    {
        strcpy(_str,that._str);
    }

    
string& operator=(const string& that)
{
    // if (this == &that)  // 自赋值检查
        // return *this;

    // delete[] _str;  // 释放旧内存

    // _str = new char[strlen(that._str) + 1];
    // strcpy(_str, that._str);
    // return *this;

    if(this == &that)
        return *this;

    delete[] _str;
    
    _str = new char(strlen(that._str) + 1);
    strcpy(_str, that._str);
    return *this;
}


private:
   char* _str;
};




}


namespace lic3
{   
    using std::endl;
    using std::cout;
    using std::cin;
    using std::ostream;
class string
{
public:
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
    {
      _size = strlen(str); //  _size依旧是有效的数字
      _capacity = _size;   //  依旧是相等的
      _str = new char[_capacity + 1]; // 多一个空间存放\0, 不算是有效的字符串，为了兼容c语言的。
      strcpy(_str, str);             //  strcpy依旧是会拷贝\0的。
    }
    
    ~string()
    {
        delete[] _str;
        _str = nullptr;
        _size = _capacity = 0;
    }
    
    // 拷贝构造
    string(const string& that)
    {
        _str = new  char[strlen(that._str) + 1];
        strcpy(_str, that._str);
        _size = that._size;
        _capacity = that._capacity;
    }
    // 赋值构造
    string& operator=(const string& that)
    {
      if(this == &that)
        return *this;
      
      delete[] _str;

      _str = new char[strlen(that._str) + 1];
      strcpy(_str, that._str);
      _size = that._size;
      _capacity = that._capacity;
      return *this;
    } 

    size_t size() const
    {
        return _size;
    }

    size_t capacity() const
    {
        return _capacity;
    }
    
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

    
    const char* c_str()
    {
        return _str;
    }

/*
 *     ostream& operator<<(ostream& out, const string& s)
 *     {
 *         for(size_t i = 0; i < s.size(); i++)
 *         {
 *             out<< s[i];
 *         }
 *
 *         return out;
 *     }
 */
        
    // 输入
    // istream& operator>>(iostream& in, const string& s)

    void push_back(char ch)
    {
        if(_size == _capacity)
        {
            size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
            char* tmp = new char[newcapacity + 1];
            strcpy(tmp, _str);
            delete  _str;
            _str = tmp;
            _capacity = newcapacity;
        }
        
        _str[_size] = ch;
        ++_size;
        _str[_size] = '\0'; // 最后一个位置你得存放斜杠零
    }
    
    void append(const char* str)
    {
        size_t len = strlen(str);
        if(_size + len > _capacity)
        {
            size_t newcapacity = _size + len;
            char* newstr = new char[newcapacity + 1];
            strcpy(newstr, _str);
            delete[] _str;
            _str = newstr;
            _capacity = newcapacity;
        }

        strcpy(_str+_size, str); // strcpy会拷贝\0的
        _size = _size + len;
    }

    void reserve(size_t n)
    {
        if(n > _capacity)
        {
            char* newstr = new char[n + 1];
            strcpy(newstr, _str);
            delete[] _str;
            _str = newstr;
            _capacity = n;
        }
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


    void resize(size_t n, char ch)
    {

    }

    // void insert(size_t pos, char ch);
    // void insert(size_t pos, const char* str);
    // void erase(size_t pos, size_t len = npos);
    // size_t find(char ch, size_t pos = 0);
    // size_t find(const char* str, size_t pos = 0);
    // bool operator<(const string& s);
    // bool operator>(const string& s);
    // bool operator<=(const string& s);
    // bool operator>=(const string& s);
    // bool operator==(const string& s);
    // bool operator!=(const string& s);
    
    
    // insert：插入字符
        void insert(size_t pos, char ch)
        {
            assert(pos <= _size);
            if (_size + 1 >= _capacity)
                reserve(_capacity * 2);

            for (size_t i = _size; i > pos; --i)
                _str[i] = _str[i - 1];

            _str[pos] = ch;
            ++_size;
            _str[_size] = '\0';
        }

        // insert：插入字符串
        void insert(size_t pos, const char* str)
        {
            assert(pos <= _size);
            size_t len = strlen(str);
            if (_size + len >= _capacity)
                reserve(_size + len + 1);

            for (size_t i = _size + len - 1; i >= pos + len; --i)
                _str[i] = _str[i - len];

            for (size_t i = 0; i < len; ++i)
                _str[pos + i] = str[i];

            _size += len;
            _str[_size] = '\0';
        }

        // erase：删除字符
        void erase(size_t pos, size_t len = npos)
        {
            assert(pos <= _size);
            if (len == npos || pos + len >= _size)
            {
                _str[pos] = '\0';
                _size = pos;
            }
            else
            {
                for (size_t i = pos + len; i <= _size; ++i)
                    _str[i - len] = _str[i];

                _size -= len;
            }
        }

        // find：查找字符
        size_t find(char ch, size_t pos = 0)
        {
            for (size_t i = pos; i < _size; ++i)
            {
                if (_str[i] == ch)
                    return i;
            }
            return npos;
        }

        // find：查找字符串
        size_t find(const char* str, size_t pos = 0)
        {
            size_t len = strlen(str);
            if (len == 0 || len > _size)
                return npos;

            for (size_t i = pos; i <= _size - len; ++i)
            {
                size_t j = 0;
                for (; j < len; ++j)
                {
                    if (_str[i + j] != str[j])
                        break;
                }

                if (j == len)
                    return i;
            }

            return npos;
        }

        // 比较函数
        int compare(const string& s) const
        {
            size_t i = 0;
            while (i < _size && i < s._size)
            {
                if (_str[i] < s._str[i]) return -1;
                if (_str[i] > s._str[i]) return 1;
                ++i;
            }
            if (_size < s._size) return -1;
            if (_size > s._size) return 1;
            return 0;
        }

        // 比较运算符
        bool operator<(const string& s) { return compare(s) < 0; }
        bool operator>(const string& s) { return compare(s) > 0; }
        bool operator<=(const string& s) { return compare(s) <= 0; }
        bool operator>=(const string& s) { return compare(s) >= 0; }
        bool operator==(const string& s) { return compare(s) == 0; }
        bool operator!=(const string& s) { return compare(s) != 0; }

        // 输出支持
        // const char* c_str() const { return _str; }
        // size_t size() const { return _size; }


private:
    char* _str;
    size_t _size;
    size_t _capacity;
    static size_t npos;
};

    size_t string::npos = -1;

    ostream& operator<<(ostream& out, const string& s)
    {
        for(size_t i = 0; i < s.size(); i++)
        {
            out<< s[i];
        }

        return out;
    }
    
void test()
{
    string s1;
    string s2("lic");
    cout<< s1 <<endl;
    cout<< s2 <<endl;

    for(size_t i = 0; i < s2.size(); i++)
    {
        s2[i] += 1;
        cout<< s2[i] << " ";
    }
    cout<<endl;

    string::iterator it = s2.begin();
    while(it != s2.end())
    {
        *it -= 1;
        cout<< *it << " ";
        it++;
    }

    cout<<endl;

// 范围for最终会被编译器替换成迭代器
// iterator begin() end()  有这三个东西才行的
// 迭代器和容器有关系的。
    for(auto e : s2)
    {
        cout<< e << " ";
    }
    cout<<endl;

    s2.push_back('x');
    s2.push_back('x');
    s2.push_back('x');
    s2.push_back('x');
    s2.push_back('x');
    s2.push_back('x');
    s2.push_back('x');
    
    s2.append("lic");
    cout<< s2 <<endl;
    s2.append("fadssssss");
    s2 += "licda";
    s2 += 'c';
    
    cout<< s2 <<endl;
}
}


int main()
{

    // test();
    lic3::test();

}

