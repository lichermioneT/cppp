#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;



void test5_multi()
{
  multiset<int> ms;
  ms.insert(33);
  ms.insert(33);
  ms.insert(34);
  ms.insert(34);
  for(auto e : ms)
  {
    cout<< e <<endl;
  }
  cout<<endl;
  
  multiset<int>::iterator it  = ms.find(33);
  cout<< *it <<endl;
  ++it;

  cout<< *it <<endl;
  ++it;

  cout<< *it <<endl;
  ++it;

  cout<< *it <<endl;

//multi_map没有operator[],多个相同的key,b不知道返回谁的valu.
}

// 题目
int main()
{
  test5_multi();
  return 0;
}


// map统计水果的次数
void test()
{
 map<string, int> s;
 string strs[] = {"西瓜","西瓜", "西瓜", "香蕉", "香蕉", "樱桃", "樱桃" };
 for(const auto& e : strs)
 {
   map<string,int>::iterator it = s.find(e);
   if(it != s.end())
   {
     it->second++;
   }
   else 
   {
     s.insert(make_pair(e, 1));
   }
 }

 for(const auto& e : s)
 {
    cout<< e.first << ":" << e.second <<endl;
 }
 cout<<endl;
}

void test2()
{
 map<string, int> s;
 string strs[] = {"西瓜","西瓜", "西瓜", "香蕉", "香蕉", "樱桃", "樱桃" };
 for(const auto& e : strs)
 {
   pair<map<string, int>::iterator, bool> ret = s.insert(make_pair(e, 1));
   if(ret.second == false)
   {
     ret.first->second++;
   }
 }

 for(const auto& e : s)
 {
    cout<< e.first << ":" << e.second <<endl;
 }
 cout<<endl;
}


// map也是搜索树呢的。
// []不管你存不存在
// k不存在就插入，value给缺省值，然后返回它的引用
// k存在了，也返回k对应value的的引用的

// map的[]实际上是调用的insert的
// insert的返回值pair的。
// pair(iterator, bool);

// 不用find,没有合适的返回呢？

// insert如果k不存在map里面，插入pair<k, mapped_type()>,在返回映射对象的引用
// k在map里面，插入失败，返回k所在节点中的映射对象的引用。

//[]
// 1.插入
// 2.找k的映射对象
// 3.修改k的映射对象
// value可以是缺省参数的

// []
// 插入+修改
// 修改
// 一般不去查找，因为不存在了，就直接插入了k,value自带缺省值的

// 1增insert operator[]
// 2删erase
// 3查find
// 4改 []
// 5变量 iterator for 
//   变量出来值是按照k，排序的呢。
// pair<k,v> 键值对呢

void test4()
{
  map<string, string> dict;
  dict.insert(make_pair("lic", "军少"));
  dict["lic2"] = "军少2";
  dict["lic3"] = "军少3";
  dict["lic4"] = "军少4";
  dict["lic4"] = "军少44444444444444444444";
  dict["xxx"];

  /*
   *map<string, string>::iterator it = dict.begin();
   */
  for(auto& e : dict)
  {
    cout<< e.first << " : " << e.second <<endl;
  }
  cout<<endl;
}

void test3()
{
 map<string, int> s;
 string strs[] = {"西瓜","西瓜", "西瓜", "香蕉", "香蕉", "樱桃", "樱桃" };
 for(const auto& e : strs)
 {
   // mapped_type& operator[] (const key_type& k);
   // (*((this->insert(make_pair(k,mapped_type()))).first)).second;
   //  this->insert(make_pair(k,mapped_type())) // 迭代器，bool 
   //  *().first .second;
   
   // 1.不在，插入
   // 2.存在，映射对象的value.
   s[e]++;
 }

 for(const auto& e : s)
 {
    cout<< e.first << ":" << e.second <<endl;
 }
 cout<<endl;
}

