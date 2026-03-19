#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;

template<class K>
struct  SetKeyOfT
{
  // functor(function object)
  const K& operator()(const K& key)
  {
    return key;
  }
};

enum State
{
  EMPTY,
  EXITS,
  DELETE
};

template<class  T>
struct hashData
{
  T _data;   // 需要存储的数据
  State _state; // 数据的状态呢
};

template<class K, class T, class KeyOfT>
class hashtable 
{
  typedef hashData<T> hashData;
public:
  // “探测到 EMPTY，说明后面不可能再有这个元素了，因为这里从来没放过数据。”
  bool insert(const T& d )
  {
    // 负载因子，表中的数据/表的大小。衡量哈希表满的程度。
    // 表越满，效率越低。
    // hashtable并不是满的才增容，开放定值法，一般是0.7开始扩容的。
    // 负载因子越小，冲突效率越低，整体效率越高，但是负载因子越小，浪费空间越大
    // 所以负载因子一般是折中
    // 闭散列的哈希表不能够满了在增容，满了在增容，效率很低的。 负载因子登场。
    // 负载因子是空间换时间的策略
    

    KeyOfT keyOft;
// 数据扩容，导致除数变化了的。
// 增容三部曲
// 1.空间开一个2倍
// 2.旧数据映射到新表 。重新映射的。
// 3.释放旧表的空间
    if(_num*10 / _table.size() >= 7)
    {
      // 1.开数据
      // 2.重新映射
      // 3.释放旧表
      vector<hashData> newTable;
      newTable.resize(_table.size());
      for(size_t i = 0; i < _table.size(); ++i)
      {
        if(_table[i]._state == EXITS)
        {

        size_t index = keyOft(_table[i]._data) % newTable.size();
        while(newTable[index]._state == EXITS)
        {
          ++index;
          if(index == _table.size())
          {
            index = 0;
          }
        }
        newTable[index] = _table[i];
      }
      }
      _table.swap(newTable);
    }

    size_t index = keyOft(d) % _table.size(); // 算数据应该在表中的位置。
    while(_table[index]._state == EXITS)
    {
      if(keyOft(_table[index]._data) == keyOft(d))
      {
        return   false;
      }

      ++index;
      if(index == _table.size())
      {
        index = 0;
      }
    }

    _table[index]._data = d;
    _table[index]._state = EXITS;
    _num++;
    return true;
  }

  hashData* find(const K& key)
  {
    KeyOfT koft;
    size_t index = key % _table.size();
    while(_table[index]._state != EMPTY)
    {
      if(_table[index]._data == key)
      {
        if(_table[index]._state == EXITS)
        {
          return &_table[index];
        }
        else if(_table[index]._state == DELETE) 
        {
          return nullptr;
        }
      }
      
      ++index;
      if(index == _table.size())
      {
          index = 0;
      }
    }
    return  nullptr;
  }

  bool erase(const K& key)
  {
    hashData* ret = find(key);
    if(ret != nullptr)
    {
      ret->_state = DELETE;
      return true;
    }
    else 
    {
      return  false;
    }
  }

private:
  vector<K> _table; // 映射的表
  size_t _num = 0;    // 存了几个数据的 
};

void test2()
{
  hashtable<int, int, SetKeyOfT<int>> ht;
  ht.insert(1);
  ht.insert(3);
  ht.insert(5);
  ht.insert(7);
  ht.insert(9);
}

int main()
{



  return 0;
}


// 1.叉搜索树，AVL树，红黑树
// 2.AVL和红黑树的规则，如何平衡
// 3.AVL和红黑树的效率
// 4.如何实现旋转
// 5.map和set实现的大致框架
// 红黑树记得规则，AVL实际上的平衡因子条件很难的。
// STL。vector/list/map/set


void test_unorder_map_set()
{
  unordered_set<int> us;
  us.insert(3);
  us.insert(4);
  us.insert(5);
  us.insert(3);
  us.insert(0);

  for(auto e : us)
  {
    cout<< e <<endl;
  }

  set<int> s;
  s.insert(1);
  s.insert(1);
  s.insert(1);
  s.insert(1);
  s.insert(3);
  s.insert(4);
  s.insert(6);

  for(auto e : s)
  {
    cout<< e <<endl;
  }
}


//1.map和set unorder_map和unorder_set.
//2.四个都可以实现key.value的搜索场景，并且使用和功能基本一样 的
//3.map/set底层红黑树，时间复杂度O(logN), 遍历出来有序的
//3.unorder_map/unorder_set底层哈希，时间复杂度O(1)，遍历出来有序的
//4.map和set是双向迭代器，unorder_map和unorder_set是单向迭代器。


// 面试题查找字符串只出现一次的字符。
// 字符串
// int a[256]:统计次数，建立映射关系。a=1,b=2,....Z。
// 统计int a[256]中的1

// 问题：出现太大的空间记录映射关系。
// 1,2,4,5,10000000。开一个太大的空间进行映射，出现问题了。
// 直接定制法：
//  abc.zA..Z
//  a-a,b-a...Z-a。
// 除留余数法(注意取模num,就是取数组[0-num-1])
// 怎么放，怎么找。 
// 
// 哈希也叫散列。
// 现在我们会发现hash冲突了
// 0...11。11放到1了。可能不同的数，映射到相同的位置了
// hash效率非常高，但是需要解决hash冲突的。
//
// 解决方案
// 1.冲突了去找下一个空位置。
// 冲突越多，效率越低 。
// 2.二叉探测。


// hash是一种映射关系的数据
// 直接定制法
// a-97=0
// a-98=1
// .....

// 除留余数法
// 除留余数法，不再是给每个值映射一个位置，在限定的大小空间中将我的值映射进去。
// index = key % capacity。
// 问题就是：不同的值的余数可能一样的，映射到相同的位置，导致哈希冲突，导致效率低下的。
// 如何解决呢？
// 1.闭散列--开放定值法(按规则再给你找个位置)
//  a.线性探测，挨着挨着往后找
//  b.二次探测，安装平方一直找
// 2.开散列--拉链法(哈希桶) 重点。

