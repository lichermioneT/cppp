#include <iostream>
#include <set>
#include <map>
using namespace std;

// 序列式容器：vector/list/string/deque 
// 关联式容器：map/set/unorderded_map/unordered_set

// set平衡搜索树
// 迭代器是中序的

// 增删查O(logN);
// 不能够进行修改的数据的。
void test1()
{
  set<int> s;
  s.insert(3);
  s.insert(2);
  s.insert(4);
  s.insert(3);
  s.insert(3);
  s.insert(7);
  set<int>::iterator it = s.begin();
  while(it != s.end())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;

  set<int> s2(s);
  for(auto& e : s2)
  {
    cout<< e << " ";
  }
  cout<<endl;


// 删除可以给迭代器(删除迭代器位置的数据)，也可以给数值(数值存在就删除，不存在就算了)
// 给值就是，用值去找的数据。
// find函数是O(N)
// 成员find函数是O(Log(N))
  set<int>::iterator it2 =s.find(3);
  if(it2 != s.end())
  {
    s.erase(it2);
  }
  for(auto& e : s)
  {
    cout<< e << " ";
  }
  cout<<endl;
}

void test2()
{
  map<int,int> m;
  m.insert(pair<int, int>(1, 1));
  m.insert(pair<int, int>(3, 3));
  m.insert(pair<int, int>(2, 2));  // 需要些模板参数的呢。
  m.insert(make_pair(4, 4));       // 不写模板参数的
  map<int, int>::iterator it = m.begin();
  while(it != m.end())
  {
    cout<< (*it).first << " : " << (*it).second <<endl;
    cout<< it->first << " : " << it->second << endl;
    ++it;
  }
  cout<<endl;

// 还可以用来统计次数的呢。
}


int main()
{
  /*
   *test1();
   */
  
  test2();

  return 0;
}
