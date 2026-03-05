#include <iostream>
#include <string>
#include <vector>
using namespace std;


// 重点的构造函数
void test()
{
    string s1;
    string s2("hello");
    string s3("hello", 3);
    string s4("01234567890", 2, 5); // 字符串+起始位置+步长
    string s5(10, 'a');             // 用N个字符拷贝的。
    string s6(s4, 2, 5);
    
    cout<< "s1: " << s1 << endl;
    cout<< "s2: " << s2 << endl;
    cout<< "s3: " << s3 << endl;
    cout<< "s4: " << s4 << endl;
    cout<< "s5: " << s5 << endl;
    cout<< "s6: " << s6 << endl;

    s1 = s4; // 赋值

//  npos
//  static const size_t npos  = -1;
//
}

// 遍历
void test2()
{

    string s("hello ");
    s += "world ";
    s += "lichermionex";
    
    string s1("!!");

    s += s1;

// 遍历字符串   

// 方法1：operator[] + 下标
     for(size_t i = 0; i < s.size(); i++)
     {
         s[i] += 1;
     }

    cout<<endl;
    for(size_t i = 0; i < s.size(); i++)
    {
        cout<< s[i] << " ";
    }
    cout<<endl;

// 方法二:迭代器
// 迭代器不一定是指针
// 这个迭代器属于这个对象里面的东西。
// 使用的是时候需要突破类域。
// iterator 
// const_iterator 
// reverse_iterator 
// const_reverse_iterator
    string::iterator it = s.begin(); // 有效数据的最后一个位置。
    while(it != s.end())
    {
        *it -= 1;
        cout<< *it << " ";
        ++it;
    }
    cout<<endl;
    
    string::const_iterator cit = s.cbegin();
    while(cit != s.cend())
    {
        cout<< *cit << " ";
        ++cit;
    }
    cout<<endl;

// end是最后面的下一个
    
    string::reverse_iterator rit = s.rbegin();
    while(rit != s.rend())
    {
        cout<< *rit << " ";
        rit++;
    }

    cout<<endl;
    
// 范围for，实际上就是迭代器
    for(auto& e : s)
    {
        cout<< (e+=1) << " ";
    }
    cout<<endl;

// 实际推荐下标和范围for
// auto关键字推荐用来接收迭代器
}



void test3()
{
    
// 迭代器四种
// 正向，反向
// 普通，const
// iterator 
// const_iterator 
// reverse_iterator 
// const_reverse_iterator

    string s("hello lichermionex ");
    auto it = s.rbegin(); // rbegin就是最后一个位置，++就是向前走的

    while(it != s.rend())
    {
        cout<< *it << " ";
        it++;
    }
    cout<<endl;

// auto关键字真的好用
// 哈哈哈哈
}



void test4()
{
    string s("91011");
    int val = 0;
    for(size_t i = 0; i < s.size(); i++)
    {
        val *= 10;
        val += (s[i] - '0');

    }
    cout<< val <<endl;
}


// size和length都是字符串的有效个数
// capacity 当前字符串能够容纳最多少个字符串而不需要重新扩容的。
void test5()
{
    string s1("afsdfads");
    string s2("12345fads0");
    
    s2 += "adsffds";
    cout<< s1.size() <<endl;
    cout<< s1.length() <<endl;
    cout<< s2.size() <<endl;
    cout<< s2.length() <<endl;

    cout<< s1.capacity() <<endl;
    cout<< s2.capacity() <<endl;
    s2.clear();
    cout<< s2.size() <<endl;
    cout<< s2.capacity() <<endl;
}


void test6()
{
    string s;
    for(int i = 0; i < 1000; i++)
    {
        s += 'c';
        if(s.size() != s.capacity())
        {
            cout<< s.capacity() <<endl;
        }
    }
}

//reserve预开辟一块空间的
void test7()
{
    string s;
    s.reserve(199); // 至少开199个空间
    cout<< s.size() <<endl;
    cout<< s.capacity() <<endl;
}

void test77()
{
  string s = "abc";
  s.reserve(10);
  cout << s << endl;        // 还是 abc
  cout << s.size() << endl; // 3

  s.resize(10, 'x');
  cout << s << endl;        // abcxxxxxxx
  cout << s.size() << endl; // 10
}

void test8()
{
    string s;
    s.resize(100);

    cout<< s.size() <<endl;
    cout<< s.capacity() <<endl;
}


void testt()
{
  string s;
  s.push_back('a');
  s += "33";
  s += 'c';
  s.append("adf");

  s.insert(s.begin(), 'x');
  s.insert(2, "2");


}

void test9()
{
    string s("123 ---daf-fads-fads--fadf-fadf-fdas-466777");
    auto bit = s.begin();
    auto eit = s.end();

    while(bit != eit)
    {
        if(*bit != '-' && *eit != '-')
        {
            char c = *bit;
            *bit = *eit;
            *eit = c;
        }
            bit++;
            eit--;
        
    }
    cout<< s <<endl;
}

class Solution {
public:
    string reverseOnlyLetters(string s) 
    {
        int left = 0;
        int right = s.size() - 1;

        while (left < right)
        {
            if (!isalpha(s[left]))
            {
                left++;
            }
            else if (!isalpha(s[right]))
            {
                right--;
            }
            else
            {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }

        return s;
    }
};

class Solution1 {
public:
    int firstUniqChar(string s) 
    {
        int count[26] = {0};
        for(auto ch : s)
        {
            count[ch - 'a']++;
        }

        for(size_t i = 0; i < s.size(); i++)
        {
            if(count[s[i] -'a'] == 1)
            return i;
        }

        return -1;
    }
};

int main()
{

//1.
// c++头文件不要带.h
// 四个默认成员函数
    
// 构造函数,一般用的时候只关心。
// 析构函数
   /*
    *test();
    */


// 遍历
    /*
     *test2();
     */

// 迭代器的种类
// 方向
// 普通和const


     /*
      *test3();
      */
    // test4();

     /*
      *test5();
      */

    // test6();



    // test7();
    // test8();

    // string s;
    // string s2("asdf");
    // s.push_back('x');
    // s.append("ssss");
    // s.append(s2);


    // cout<< s <<endl;

    // s.clear();

    // s += "123456";
    // s.insert(s.begin(), '0');
    // cout<< s <<endl;

    // s.insert(2, "w");
    // cout<< s <<endl;

    // s.erase(2,3);
    // cout<< s <<endl;
    
    /*
     *test9();
     */











    return 0;
}

