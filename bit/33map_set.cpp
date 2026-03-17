#include <iostream>
using namespace std;

// 二叉搜索树近端情况退化成链表了O(n)
// 解决方案1AVL树: 高度平衡的，左右子树的高度差不超过1。 O(logN)       严格平衡的
// 解法方案2红黑树：要求最长路径不超过最短路径的2倍。可能是：2*O(logN) 近似平衡
//
// 1.根节点是黑色
// 2.每条路径的黑色节点一样的
// 3.红色节点不能够连续的
// 4.NULL也是黑色的
// 5.不是黑色就是红的。
//
// 最短：全黑
// 最长：一黑一红的。
//
//
// 1空树，插入节点当做根，把它变黑
// 2.插入红色的节点，父亲是黑色的，结束了
// 3.插入红色的节点，父亲是红色的，祖父存在且是黑色的，
//    判断叔叔的情况
//   a.叔叔存在且为且为红色的，简单 parent和uncle变黑，grandfather变红。这样一变黑色节点数量不变的。继续往上处理了
//   b.叔叔存在且为黑色或者不存在的，旋转+变色。可能单旋或者双旋转的。
//      直线单旋
//      折线双旋
//

enum color 
{
  black,
  red,
};

template<class T>
struct RBTreeNode
{
  RBTreeNode(const T& data)
    :_left(nullptr)
    ,_right(nullptr)
    ,_parent(nullptr)
    ,_data(data)
    ,_col(red)
  {}
  RBTreeNode<T>* _left;
  RBTreeNode<T>* _right;
  RBTreeNode<T>* _parent;
  T _data;
  color  _col;
};

template<class T>
struct __TreeIterator
{
typedef RBTreeNode<T> Node;
typedef __TreeIterator<T> self;
  __TreeIterator<T>(Node* node)
    :_node(node)
  {

  }
Node* _node;
  
    T& operator*()
    {
      return _node->_data;
    }

    T* operator->()
    {
      return &_node->_data;
    }
    
    self& operator++() // 前置++
    {
      // 右边为空，就是访问子树访问完成了的。
      if(_node->_right) // 右子树不是空的，则中序就是右子树的最小值的
      {
        Node* subLeft = _node->_right;
        while(subLeft->_left != nullptr)
        {
          subLeft = subLeft->_left;
        }
        _node = subLeft;
      }
      else // 右为空，子树访问完成了的，下一个节点去祖先里面找了。 
      {    // 去找父亲的父亲(祖先)
          Node* cur = _node;
          Node* parent = cur->_parent;
          while(parent && cur == parent->_right)
          {
            cur = cur->_parent;
            parent = parent->_parent;
          }
          _node = parent;
      }
      return *this;     
    }

    self& operator--() // 前置--
    {
      
      return *this;
    }

    bool operator!=(const self& s)
    {
      return _node != s._node; // s->_node
    }

};


template<class k, class T, class KOfT>
class RBTree 
{
typedef RBTreeNode<T> Node;
public:
    typedef __TreeIterator<T> iterator;  
      
    iterator begin()
    {
      Node* cur = _root;
      while(cur != nullptr && cur->_left != nullptr)
      {
        cur = cur->_left;
      }

      return iterator(cur);
    }

    iterator end()
    {
      return nullptr;
    }

  bool insert(const T& data) 
  {
    if(_root == nullptr)
    {
      _root = new Node(data);
      _root->_col = black; // 1.根节点是黑色的。
      return true;
    }
    
    KOfT koft;
    
    
    Node* parent = nullptr;
    Node* cur = _root;

// 1.安装搜索树的规则进行插入进去了
    while(cur != nullptr)
    {
      if(koft(cur->_data) < koft(data)) // 数据取出来进行了的
      {
        parent = cur;
        cur = cur->_right;
      }
      else if(koft(cur->_data) > koft(data)) // 数据取出来进行了的比较的
      {
        parent = cur;
        cur = cur->_left;
      }
      else 
      {
        return  false;
      }
    }
    
    cur = new  Node(data);
    if(koft(parent->_data) < koft(cur->_data)) // 取出来数据
    {
      parent->_right = cur;
      cur->_parent = parent;
    }
    else 
    {
      parent->_left = cur;
      cur->_parent = parent;
    }


// 1.新插入的节点给黑色还是红的。肯定是红的。
//  关键看叔叔：叔叔存在且为红
//              cur插入红的
//              p,u变成黑色的。g变成红色的。一红一黑则黑色的节点不变的。！
//  1.g可能是根节点呢，直接变成黑色的就行了的。结束了。
//  2.g不是跟，g的父亲是黑色就结束了。
//             g的父亲是红色,继续往上处理
//
// 抽象图片：
// cur可能是新增的节点呢，也有可能是下面子树的祖父，原来是黑色的，是由于变色，变色处理成红色上来的。
// 但是不管是什么情况变上来的，这里处理情况是一样的，u存在且为红，p和u变黑，g变红的 继续向上处理
//
// 总结：关键是看u是否存在且为红的
// ps:需要注意的是，这里只关注颜色，而p,g,u几个节点在左边或者在右边都是一样的。
//
// 情况2：
// cur红，p红 (u不存在，u为黑色的)
//  旋转+变色了(麻烦玛法)
//
// 情况3：
// 双旋的情况,出现了折线的情况了。
//
    cur->_col = red;
    while(parent && parent->_col == red)
    {
      Node* grandfather = parent->_parent;


      if(grandfather->_left == parent)
      {
        Node* uncle = grandfather->_right; // 叔叔在右边的情况
        if(uncle && uncle->_col == red)
        {
          parent->_col = uncle->_col = black; //  这里是子树一红一黑，变化了才没有颜色差的问题。
          grandfather->_col = red;
          
          // 继续往上处理了。
          cur = grandfather;
          parent = cur->_parent;
        }
        else // 情况2和情况3,叔叔不存在，叔叔存在且为黑色。
        {
          // 情况三：双旋-》单旋
          if(cur == parent->_right)
          {
            RotateL(parent);
            std::swap(parent, cur);
          }

          // 情况2
          RotateR(grandfather);
          grandfather->_col = red;
          parent->_col = black;
    
          break;
        }
      }
      else // 叔叔在左边的情况
      {
          Node* uncle = grandfather->_left;
          if(uncle && uncle->_col == red)
          {
            parent->_col = uncle->_col = black;
            grandfather->_col = red;

            cur = grandfather; // 继续往上更新了
            parent = cur->_parent;
          }
          else // 看你是哪一种旋转了 
          {
              if(cur == parent->_left)
              {
                RotateR(parent);
                std::swap(parent, cur);
              }
              RotateL(grandfather);

              grandfather->_col = red;
              parent->_col = black;
              break;
          }
      }
    }
  
    _root->_col = black;

    return true;
  }

  void RotateL(Node* parent)
  {
    Node* pparent = parent->_parent;
    Node* subR  =  parent->_right;
    Node* subRL = subR->_left;
    
    parent->_right = subRL; // 接上去
    if(subRL != nullptr)
        subRL->_parent = parent; //subRL可能是空的呢。小心小心  
                        
    subR->_left = parent; // 拉下来了的
    parent->_parent = subR;

    //1.原来parent是这颗树的根，现在是subR了
    if(_root == parent)
    {
      _root = subR;
      subR->_parent = nullptr;
    }
    //2.parent不是这颗树的根,需要和以前的链接起来的。
/*  x
 *1 parent 
 * 2  subR
 *   3
 */
    else 
/*x
 * 1 parent 
 *  2  subR
 *   3
 */
    {
       if(pparent->_left == parent)
       {
         pparent->_left = subR;
       }
       else 
       {
         pparent->_right = subR;
       }

       subR->_parent = pparent;
    }
  }


//     1
//   2
// 3
private:
  void RotateR(Node* parent)
  {
    Node* pparent = parent->_parent;
    Node* subL = parent->_left;
    Node* subLR = subL->_right;
    
    parent->_left = subLR;
    if(subLR != nullptr)  // 了能是空的。
      subLR->_parent = parent;
    
    subL->_right = parent; // 拉下来了的
    parent->_parent = subL; // 下来
    
    if(_root == parent)
    {
      _root = subL;
      subL->_parent = nullptr;
    }
    else 
    {
      if(pparent->_left == parent)
      {
        pparent->_left = subL;
      }
      else 
      {
        pparent->_right = subL;
      }
      subL->_parent = pparent;
    }
  }

public:
void _InOrder(Node* root)
{
    if (root == nullptr)
        return;
    _InOrder(root->_left);
    KOfT koft;
    cout<< koft(root->_data) << " ";

    _InOrder(root->_right);
}

void InOrder()
{
    _InOrder(_root);
    cout << endl;
}

// [新增1] 对外验证红黑树
bool IsValidRBTree()
{
  if(_root == nullptr)
    return true;

  // 性质1：根节点必须是黑色
  if(_root->_col != black)
  {
    cout << "违反性质1：根节点必须是黑色" << endl;
    return false;
  }

  // 先统计一条路径上的黑色节点数量（这里取最左路径）
  size_t blackCount = 0;
  Node* cur = _root;
  while(cur)
  {
    if(cur->_col == black)
      ++blackCount;

    cur = cur->_left;
  }

  return _IsValidRBTree(_root, 0, blackCount);
}

// [新增2] 递归检查红黑树性质
bool _IsValidRBTree(Node* pRoot, size_t K, const size_t blackCount)
{
  // 走到空节点，检查当前路径黑色节点数是否一致
  if(pRoot == nullptr)
  {
    if(K != blackCount)
    {
      cout << "违反性质4：每条路径中黑色节点的个数必须相同" << endl;
      return false;
    }
    return true;
  }

  // 统计黑色节点个数
  if(pRoot->_col == black)
    ++K;

  // 性质3：不能有连续的红色节点
  Node* pParent = pRoot->_parent;
  if(pParent && pParent->_col == red && pRoot->_col == red)
  {
    cout << "违反性质3：不能有连续的红色节点" << endl;
    return false;
  }

  return _IsValidRBTree(pRoot->_left, K, blackCount)
      && _IsValidRBTree(pRoot->_right, K, blackCount);
}


  Node* find(const k& key)
 {
   KOfT koft;
    Node* cur = _root;
    while(cur != nullptr)
    {
      if(koft(cur->_data) < key)
      {
        cur = cur->_right;
      }
      else if (koft(cur->_data) > key)
      {
        cur = cur->_left;
      }
      else 
      {
        return cur;
        break;
      }
    }
    return nullptr;
 }

private:
  Node* _root = nullptr;
};



template<class k, class v>
class mymap 
{
public:
  struct MapKeyOfT
  {
    const k& operator()(const pair<k,v>& kv) //仿函数
    {
      return kv.first;
    }
  };
  typedef typename RBTree<k, pair<k,v>, MapKeyOfT>::iterator iterator;

  iterator begin()
  {
    return _t.begin();
  }

  iterator  end()
  {
    return _t.end();
  }
  bool insert(const pair<k,v>& kv)
  {
    return _t.insert(kv);
  }

    // [新增] 暴露验证接口
  bool IsValidRBTree()
  {
    return _t.IsValidRBTree();
  }

  // [新增] 暴露中序
  void InOrder()
  {
    _t.InOrder();
  }
private:
  RBTree<k, pair<k,v>, MapKeyOfT> _t;
};

void test()
{
    mymap<int, int> m;
  m.insert(make_pair(1, 1));
  m.insert(make_pair(3, 3));
  m.insert(make_pair(2, 2));
  m.insert(make_pair(5, 5));
  m.insert(make_pair(4, 4));
  m.insert(make_pair(6, 4));
  m.insert(make_pair(99, 4));
  m.insert(make_pair(43, 4));
  m.insert(make_pair(77, 4));
  m.insert(make_pair(33, 4));

  mymap<int,int>::iterator it = m.begin();
  while(it != m.end())
  {
    cout<< it->first << ":" << it->second <<endl;
    ++it;
  }
  cout<<endl;
}


template<class k>
class mymset
{
public:

  struct SetKeyOfT
  {
    const k& operator()(const k& t )
    {
      return t;
    }
  };

public:
  typedef typename RBTree<k, k, SetKeyOfT>::iterator iterator;

  iterator begin()
  {
    return _t.begin();
  }

  iterator  end()
  {
    return _t.end();
  }

  bool insert(const k& key)
  {
    return _t.insert(key);
  }
  
    // [新增] 暴露验证接口
  bool IsValidRBTree()
  {
    return _t.IsValidRBTree();
  }

  // [新增] 暴露中序
  void InOrder()
  {
    _t.InOrder();
  }
private:
  RBTree<k, k,SetKeyOfT> _t;
};

void test1()
{
    mymset<int> s;
  s.insert(3);
  s.insert(1);
  s.insert(5);
  s.insert(2);
  s.insert(4);

  // [新增] 验证
  /*
   *cout << "mymset 是否为红黑树: " << s.IsValidRBTree() << endl;
   *s.InOrder();
   */

  mymset<int>::iterator it =  s.begin();
  while(it != s.end())
  {
      cout<< *it << " ";
      ++it;
  }
  cout<<endl;
}

// 实际上map和set是一颗红黑树实现的。
// 两个红黑树冗余了
// 想办法复用
// _Rb_tree,最基本的红黑树模板
// 它的核心思想是：将“树节点存储的实际数据（Value）”与“用于排序比较的键值（Key）”解耦。

int main()
{
  test();
  test1();
  return 0;

}
// 1.二叉搜索树，存储数据的同时方便进行高效的搜索(在此之前都是的数据结构基本都是进行的暴力搜索)
//   缺点：有序的方式进行插入，二叉树退化成单链表形式，效率O(N),效率低下。
// 2.AVL登场，二叉搜索树的基础上加一个条件：左右子树的高度差不能超过1,(-1,0,1)。并且左右子树都满足的。
//  增删查改搜索的效率非常高O(logN)。内存可以的情况下，全中国的信息放到里面，只需要31次就行了的。
// 3.红黑树。登场了。

// 1.增删查改。增删。查简单，不可改的。
//  增：a,按照搜索树进行插入了。b,更新平衡因子了。c平衡因子出现-2、2。判断是四种情况的哪一种呢？
//  删：a,安装搜索树的规则删除，b,更新平衡因子了。c平衡因子变化了，判断是哪一种，旋转。
//                                和上面的相反了。
// 
// 1.右边插入，父亲平衡因子++，左边插入，父亲平衡因子--
//   右边删除，父亲平衡因子--，左边删除，父亲平衡因子++
// 2.插入后，父亲的平衡因子变成0，说明父亲所在的数高度不变，更新结束了。
//   删除后，父亲的平衡因子变成0，说明父亲所在的数高度变了，继续更新。？？
// 3.插入后，父亲的平衡因子变成1/-1，说明父亲所在的数高度变了，继续更新
//   删除后，父亲的平衡因子变成1/-，说明父亲所在的数高度不变，更新结束了。？？
// 4.插入删除，父亲的平衡因子变成2、-2.不平衡，旋转处理了。
//
// 查和改：不允许修改的。修改了可能破坏整个树，key/value可以修改value的
// 查和改和二叉树一样的。



// AVL严格的平衡二叉树
// 红黑树
// 1.搜索二叉树，节点 加了颜色不是黑就是红，树最长的路径不超过最短路径的2倍。
// 
// 红黑树
// 1.不是黑就是红
// 2.根节点黑
// 3.如果节点是红色，两个孩子是黑色的，
//    不存在连续的红节点
// 4.每个节点到所有后代的的叶子节点，均包含相同数目的黑色节点
// 5.叶子节点(空节点)都是黑色的。空节点。空节点是黑色的。
//   ?为什么长的不会超过短两倍。

// a.根式黑的
// b.不存在连续的红
// c.每条路径的黑色一样的。
//  最短全黑
//  最长一黑一红的。
// 全黑：时间复杂度O(LogN)
// 一黑一红：时间复杂度2O(LogN)
//  虽然红黑树略差AVL，现在硬件的速度很快，常规数据中LogN和2LogN差异不大了
//
//为什么AVL树和红黑树性能基本相差2倍，但是我们认为基本一样呢？硬件足够的快。10亿数据
//AVL30次，红黑树最多60次。现在30和60基本一致的。
// 红黑树插入删除节点比AVL树旋转更少，
// AVL通过更加严格的多次旋转达到了。
// 所以红黑树实现更容易控制的
//




