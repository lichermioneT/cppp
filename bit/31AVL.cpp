#include <iostream>
using namespace std;

//1AVL树
//左右子树的高度差不相差1呢。
//这里我们用平衡因子来实现的
// 平衡因子： 右子树的高度 减法 左子树的高度。
// 基本控制在O(logN)

template<class k, class v>
struct AVLTreeNode
{
  AVLTreeNode(const pair<k,v>& kv)
    :_left(nullptr)
    ,_right(nullptr)
    ,_parent(nullptr)
    ,_bf(0)
    ,_kv(kv)
    {}
  AVLTreeNode<k, v>* _left;
  AVLTreeNode<k, v>* _right;
  AVLTreeNode<k, v>* _parent;
  int _bf;
  pair<k,v> _kv;
};

template<class k, class v>
class AVLTree 
{
typedef AVLTree<k, v> node;
public:
  
  // 插入三部曲呢。
  // 1.按搜索二叉树插入
  // 2.更新平衡因子
  // 3.出现问题旋转(根据旋转因子判断的。)
  
  // bf只能是-1，0, 1
  // 插入一个节点只会影响它的祖先的。但是不是所有的祖先都会受到影响的。
  //  1.新增节点自己bf=0;左边插入，parent的bf-- ,右边插入，parent的bf++
  //  2.更新父亲的bf，如果bf==0,更新完成了，说明parent的高度不变了，更新结束，插入完成了。(刚好把父亲矮的那边填充上了的。)
  //  3.如果更新完成parent 的bf == -1 或 bf == 1。(更新前父亲bf == 0，现在变成-1或者1.说明一边低或者一边高了的。) 说明parent的高度变了，需要继续更新的。
  //  4.如果parent->bf == 2或者 bf==-2.出现问题呢，需要旋转处理的。
  //  
  bool insert(const pair<k, v>& kv)
  {
    if(_root == nullptr)
    {
      _root = new node(kv);
      return true;
    }

    node* parent = nullptr;
    node* cur = _root;
    while(cur != nullptr)
    {
      if(cur->_kv.flist > kv.first)
      {
        parent = cur;
        cur = cur->_left;
      }
      else if(cur->_kv.first < kv.first)
      {
        parent = cur;
        cur = cur->_right;
      }
      else 
      {
        return false;
      }
    }
    
    cur = new node(kv);  // cur就是新的节点
    if(parent->_kv.first < kv.first)
    {
       parent->_right = cur;
       cur->_parent = parent;
    }
    else 
    {
      parent->_left = cur;
      cur->_parent = parent;
    }

    // 更新平衡因子的呢
    while(parent != nullptr)
    {
      if(cur == parent->_right)
      {
        parent->_bf++;  // 右边插入，平衡因子++
      }
      else 
      {
        parent->_bf--; // 左边插入，平衡因子--
      }

      if(parent->_bf == 0) // 最完美的情况，把低那一边的填上了的。
      {
        break;
      }
      else if(parent->_bf == -1 || parent->_bf == 1)
      {
        cur = parent;
        parent = cur->parent;  // 继续向上找了,出现了问题了的。
      }
      else if(parent->_bf == -2 || parent->_bf == 2)
      {
          // 出现问题需要进行旋转了的。
          // 1.旋转点 前提是他依旧是搜索二叉树
          // 2.旋转成平衡树
          // 3.高度恢复到之前的样子呢。
          if(parent->bf == 2)
          {
            if(cur->_bf == 1)
            {
              RotateL(parent);
            }
            else if(cur->_bf == -1)
            {
              //  
            }
          }

          if(parent->_bf == -2)
          {
            if(cur->_bf == -1)
            {
              RotateR(parent);
            }
            else if (cur->_b == 1)
            {
              // 
            }
          }

          break;
          // 旋转完成了，需要调整了，直接出去了呢。
          // 旋转完成了。恢复到parent所在树的高度，插入节点前的高度
          // 如果时子树完成更新了！！！！
      }
    }
    return true;
  }

private:
  void RotateL(node* parent)
  {
    node* pparent = parent->_parent;
    node* subR  =  parent->_right;
    node* subRL = subR->_left;
    
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
    parent->_bf = subR->_bf  = 0;
  }


//     1
//   2
// 3
private:
  void RotateR(node* parent)
  {
    node* pparent = parent->_parent;
    node* subL = parent->_left;
    node* subLR = subL->_right;
    
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
    parent->_bf = subL->_bf = 0;
  }

private:
  node* _root = nullptr;
};

/*
 *1 parent 
 * 2  subR
 *   3
 */

//左边单旋转
//1.subR的左边给parent的右边
//2.parent编程subR的左边
//subR变成了树的根了
//左边单旋，就是把左边高的拉下来了的。

/*
 *    1
 *  2
 *3
 */

int main()
{











  return 0;
}
