#include <iostream>
#include <string>

// 若它的左子树不为空，则左子树上所有节点的值都小于根节点的值
// 若它的右子树不为空，则右子树上所有节点的值都大于根节点的值
// 它的左右子树也分别为二叉搜索树
// LogN, 查找树的高度次。
// 排序中序遍历的。
// 搜索二叉树也叫做排序二叉树

using namespace std;
template<class k, class v>
struct BSTreeNode
{
    BSTreeNode(const k& key, const v& value )
        :left(nullptr)
        ,right(nullptr)
        ,_Key(key)
        ,_value(value)
    {}
    BSTreeNode* left;
    BSTreeNode* right;
    k _Key;
    v _value;
};

template<class k, class v>
class BSTree
{
    typedef struct BSTreeNode<k, v> Node;
public:

    bool Insert(const k& key, const v& value) // 不允许重复数据
    {
        if(_root == nullptr)
        {
            _root = new Node(key, value);
            return true;   
        }
        
        Node* cur = _root;
        Node* parent = nullptr; // 基类最后一个需要插入的节点呢。

        while(cur != nullptr)
        {
            if(cur->_Key < key) // 比我的大，放右边
            {   
                parent = cur;
                cur = cur->right;
            }
            else if(cur->_Key > key) // 比我的小，放左边
            {
                parent = cur;
                cur = cur->left;
            }
            else                   // 数据不能冗余的
            {
                return false;
            }
        }

        // 这里判断最后的左右
        // 然后连接起来
        // 这里的cur肯定是空的，空的我们才结束循环的。
        cur = new Node(key, value); // 新节点的指针呢，需要和父亲链接起来的。
        if(parent->_Key < key) // 比我大，放右边 
        {
            parent->right = cur;
        }
        else                    // 比我小，放左边的。
        {
            parent->left = cur;
        }
        // 到这来就可能存在相等的情况了的。

        return true;
    }

    void _InOrder(Node* root)
    {
        if(root == nullptr)
            return;
        _InOrder(root->left);
        cout<< root->_Key << " " << root->_value <<endl;
        _InOrder(root->right);
    }

    void InOrder()
    {
        _InOrder(_root);
        cout<<endl;
    }

    Node*  Find(const k& key)
    {
        Node* cur = _root;
        while(cur != nullptr)
        {
            if(cur->_Key > key)
            {
                cur = cur->left;
            }
            else if(cur->_Key < key)
            {
                cur = cur->right;
            }
            else
            {
                return cur;
            }
        }
        return nullptr;
    }

    // 替换法左子树最大
    // 替换法右子树最小
    // 左边空
    // 右边空

    bool Erase(const k&  key)
    {
        Node* cur  =  _root;
        Node* parent = nullptr;

        while(cur != nullptr)
        {
            if(cur->_Key < key)
            {
                parent  = cur;
                cur = cur->right;
            }
            else if(cur->_Key > key)
            {
                parent = cur;
                cur = cur->left;
            }
            else // 找到了需要删除的节点了。
            {

              /*
               *       5
               *   3      7
               *     4      8
               *    
               *    
               *
               */
                if(cur->left == nullptr)   // 
                {   
                    if(cur == _root)
                    {
                        _root = cur->right; // 删除_root节点的。
                    }
                    else  // 看我原来是父亲的左边右边的。
                    {
                        if(parent->right == cur) // 删除7位置的
                        {   

                            parent->right = cur->right;
                        }
                        else
                        {
                            parent->left = cur->right;   // 删除3的位置的
                        }
                    }
                    delete cur;
                }
                /*
                 *
                 *      5
                 *  3      7
                 *1      6
                 *
                 */
                else if(cur->right == nullptr)
                {
                    if(cur == _root)
                    {
                        _root = cur->left;
                    }
                    else
                    {
                        if(parent->left == cur) // 删除3位置
                        {
                            parent->left = cur->left;
                        }
                        else
                        {
                            parent->right = cur->left; // 删除7位置的呢。
                        }
                    }
                    delete cur;
                }
                /*
                 *
                 *      5
                 *  3       7
                 *1  4    6  8 
                 *
                 */
                else
                {   

      /*
       *  50
       * /  \
       *30   70
       *   /  \
       *  60   80
       *     /  \
       *    75   90
       */

      /*
       *  50
       * /  \
       *30   75
       *   /  \
       *  60   80
       *        \
       *         90
       */
                  // 右边树最小的位置。
                    Node* rightMinParent = cur; //  最小值的父节点

                    Node* rightMin = cur->right; // 最小值的位置
                    while(rightMin->left != nullptr) // 如果他只有一个节点他根本不会进去的呢。
                    {   
                        rightMinParent = rightMin;
                        rightMin = rightMin->left;
                    }

                    cur->_Key = rightMin->_Key;

                    // if(rightMinParent == nullptr)  
                    // {
                    //     // 说明 rightMin 就是 cur->right
                    //     cur->right = rightMin->right;
                    // }
                    // else
                    // {
                    //     // 正常情况：删除 rightMin
                    //     rightMinParent->left = rightMin->right;
                    // }
                    
                    // rightMin是左边为空，父亲指向它的右边。
      /*
       *  8
       * / \
       *4   15
       *   /
       *  10  rmp 
       * /
       *9  rm 
       * \
       *  9.5  
       */
                    if(rightMin == rightMinParent->left)
                    {
                        rightMinParent->left = rightMin->right; // 这是找到了右边最小的，去变量出来的。
                    }
                    else
                    {
                        rightMinParent->right = rightMin->right;// 循环没有进去，直接就是rim
                    }
  /*
   *  8 rmp 
   * / \
   *4   10 rm
   *     \
   *      12
   */
                    delete rightMin;
                }

                return true;
            }
        }

        return false;
    }

private:
    Node* _root = nullptr;
};


void test()
{       
  BSTree<string, string> dict;
  dict.Insert("sort", "排序");
  dict.Insert("string", "字符串");
  dict.Insert("tree", "树");
  dict.Insert("insert", "插入");

  string  str;
  while(cin>>str)
  {
    BSTreeNode<string, string>* ret = dict.Find(str);
    if(ret != nullptr)
    {
      cout<< ret->_value <<endl;
    }
    else 
    {
      cout<< "没有中文翻译" <<endl;
    }
  }
}

void test2()
{
  string strs[] = {"西瓜", "西瓜","西瓜", "香蕉", "香蕉","苹果", "苹果" };
  BSTree<string, int> num;
  for(auto e : strs)
  {
    BSTreeNode<string, int>* ret = num.Find(e);
    if(ret == nullptr) // 没有就插入
    {
      num.Insert(e, 1);
    }
    else 
    {
      ret->_value++; // 有就++
    }
  }
  num.InOrder();
}



// key模型，判断在不在的
// key/value模型，通过key找value

// 中英互译
// 统计次数的

// 缺陷出来了
// 会退化成链表的(插入的数据接近有序的，或者有序的) 
// Log(N) 最坏的情况 O(N)
// AVL, 红黑树登场。    

// 注意搜索树中的key不允许修改的，只能够 修改value的。

int main()
{
// 它是一颗二叉树
// 左子树的节点小于右子树

// 使用场景搜索
// 最多只需要查找树的高度次

// 排序
// 中序遍历数据有序
// 搜索二叉树也叫排序二叉树

  test2();
    return 0;
}
