#include <iostream>
#include <algorithm>
#include <list>
using namespace std;


void test5()
{
  list<int> lt1;
  for(size_t  i = 0; i < 10; i++)
  {
    lt1.push_back(i);
  }
  
  list<int>::iterator it = lt1.begin();
  while(it != lt1.end())
  {
    if(*it % 2 == 0)
    {
      it = lt1.erase(it); // erase返回值是删除数据的下一位位置。
    }
    else 
    {
      ++it;
    }
  }
  
  for(auto& e : lt1)
  {
    cout<< e << " ";
  }
  cout<<endl;
}

int main()
{
//学习容器，容器的构造函数，析构，=
//反向迭代器，反着走的, 所以是++的
  test5();
    return 0;
}

void test1()
{
    list<int> l;
    l.push_back(2);
    l.push_back(2);
    l.push_back(2);
    l.push_back(2);
    l.push_back(2);
    l.push_back(2);
    l.push_front(3);

    list<int>::iterator it  = l.begin();
    while(it != l.end())
    {
        cout<< *it <<"  ";
        it++;
    }
    cout<<endl;

    for(auto e : l)
    {
        cout<< e << "  ";
    }
    cout<<endl;

    list<int>::reverse_iterator rit = l.rbegin();
    while(rit != l.rend())
    {
        cout<< *rit << "  ";
        rit++;
    }
    cout<<endl;
}



// b cb 
// rb crb
void print_list(const list<int>& li)
{
  list<int>::const_iterator it = li.cbegin();
  while(it != li.cend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

void test2()
{
  list<int> lt1;
  lt1.push_back(1);
  lt1.push_back(2);
  lt1.push_back(3);
  lt1.push_back(4);
  
  list<int>::iterator it1 = lt1.begin();
  while(it1 != lt1.end())
  {
    cout<< *it1 << " ";
    ++it1;
  }
  cout<<endl;

  list<int> lt2(lt1);
  lt2.push_back(10);
  print_list(lt2);

  list<int> lt3(lt2);
  lt3.push_back(11);
  lt3.push_back(13);

  lt1 = lt3;

  for(auto e : lt1)
  {
    cout<< e << " ";
  }
  cout<<endl;
}



void print_cons_list(const list<int>& lt)
{
  list<int>::const_reverse_iterator it = lt.crbegin();
  while(it != lt.crend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}


void test3()
{
  list<int> lt1;
  lt1.push_back(1);
  lt1.push_back(2);
  lt1.push_back(3);
  lt1.push_back(4);
  lt1.push_back(5);

  list<int>::reverse_iterator  it = lt1.rbegin();
  while(it != lt1.rend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;

  print_cons_list(lt1);
}


void test4()
{
  list<int> lt;
  lt.push_back(1);
  lt.push_back(2);
  lt.push_back(3);
  lt.push_back(4);
  lt.push_front(4);
  lt.push_front(100);
  lt.push_front(3);
  lt.push_front(2);
  lt.push_front(1);
  
  for(auto e : lt)
  {
    cout<< e << " ";
  }
  cout<<endl;


// find函数注意判断 不等于end();
  list<int>::iterator pos = find(lt.begin(), lt.end(), 100); // find函数[)
  if(pos != lt.end())
  {
    lt.insert(pos, 8888); // 迭代器失效了吗, insert插入返回迭代器的位置是，插入的那个数据
    lt.erase(pos);        // erase是删除数据的下一个位置的
  }

  for(auto e : lt)
  {
    cout<< e << " ";
  }
  cout<<endl;
}

