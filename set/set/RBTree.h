//
//  RBTree.h
//  set
//
//  Created by 暖暖 on 2023/5/21.
//

#ifndef RBTree_h
#define RBTree_h

#pragma once

enum Colour
{
    RED,
    BLACK,
};

template<class T>
struct RBTreeNode
{
    RBTreeNode<T>* _left;
    RBTreeNode<T>* _right;
    RBTreeNode<T>* _parent;
    T _data;
    Colour _col;

    RBTreeNode(const T& data)
        :_left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)
        , _data(data)
        , _col(RED)
    {}
};

template<class T, class Ref, class Ptr>
struct __RBTreeIterator
{
    typedef RBTreeNode<T> Node;
    typedef __RBTreeIterator<T, Ref, Ptr> Self;
    Node* _node;

    __RBTreeIterator(Node* node)
        :_node(node)
    {}

    // 1、typedef __RBTreeIterator<T, T&, T*> itertaor;  拷贝构造
    // 2、 typedef __RBTreeIterator<T, const T&, const T*> const_itertaor;
    //  支持普通迭代器构造const迭代器的构造函数

    __RBTreeIterator(const __RBTreeIterator<T, T&, T*>& it)
        :_node(it._node)
    {}

    Ref operator*()
    {
        return _node->_data;
    }

    Ptr operator->()
    {
        return &_node->_data;
    }

    bool operator!=(const Self& s)
    {
        return _node != s._node;
    }

    Self& operator++()
    {
        if (_node->_right)
        {
            // 1、右不为空，下一个就是右子树的最左节点
            Node* subLeft = _node->_right;
            while (subLeft->_left)
            {
                subLeft = subLeft->_left;
            }

            _node = subLeft;
        }
        else
        {
            // 2、右为空，沿着到根的路径，找孩子是父亲左的那个祖先
            Node* cur = _node;
            Node* parent = cur->_parent;
            while (parent && cur == parent->_right)
            {
                cur = parent;
                parent = parent->_parent;
            }

            _node = parent;
        }

        return *this;
    }

    Self& operator--()
    {
        if (_node->_left)
        {
            // 1、左不为空，找左子树最右节点
            Node* subRight = _node->_left;
            while (subRight->_right)
            {
                subRight = subRight->_right;
            }

            _node = subRight;
        }
        else
        {
            // 2、左为空，孩子是父亲的右的那个祖先
            Node* cur = _node;
            Node* parent = cur->_parent;
            while (parent && cur == parent->_left)
            {
                cur = parent;
                parent = parent->_parent;
            }

            _node = parent;
        }

        return *this;
    }
};

// 仿函数
template<class K, class T, class KeyOfT>
class RBTree
{
    typedef RBTreeNode<T> Node;
public:
    ~RBTree()
    {
        _Destroy(_root);
        _root = nullptr;
    }
public:
    typedef __RBTreeIterator<T, T&, T*> itertaor;
    typedef __RBTreeIterator<T, const T&, const T*> const_itertaor;

    itertaor begin()
    {
        Node* cur = _root;
        while (cur && cur->_left)
        {
            cur = cur->_left;
        }

        return itertaor(cur);
    }

    itertaor end()
    {
        return itertaor(nullptr);
    }

    const_itertaor begin() const
    {
        Node* cur = _root;
        while (cur && cur->_left)
        {
            cur = cur->_left;
        }

        return const_itertaor(cur);
    }

    const_itertaor end() const
    {
        return const_itertaor(nullptr);
    }

    Node* Find(const K& key)
    {
        Node* cur = _root;
        KeyOfT kot;
        while (cur)
        {
            if (kot(cur->_data) < key)
            {
                cur = cur->_right;
            }
            else if (kot(cur->_data) > key)
            {
                cur = cur->_left;
            }
            else
            {
                return cur;
            }
        }

        return nullptr;
    }

    pair<itertaor, bool> Insert(const T& data)
    {
        if (_root == nullptr)
        {
            _root = new Node(data);
            _root->_col = BLACK;

            return make_pair(itertaor(_root), true);
        }

        KeyOfT kot;
        Node* parent = nullptr;
        Node* cur = _root;
        while (cur)
        {
            if (kot(cur->_data) < kot(data))
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (kot(cur->_data) > kot(data))
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                return make_pair(itertaor(cur), false);
            }
        }

        cur = new Node(data);
        Node* newnode = cur;
        if (kot(parent->_data) > kot(data))
        {
            parent->_left = cur;
        }
        else
        {
            parent->_right = cur;
        }
        cur->_parent = parent;

        while (parent && parent->_col == RED)
        {
            Node* grandfather = parent->_parent;
            if (grandfather->_left == parent)
            {
                Node* uncle = grandfather->_right;
                // 情况1：u存在且为红，变色处理，并继续往上处理
                if (uncle && uncle->_col == RED)
                {
                    parent->_col = BLACK;
                    uncle->_col = BLACK;
                    grandfather->_col = RED;

                    // 继续往上调整
                    cur = grandfather;
                    parent = cur->_parent;
                }
                else // 情况2+3：u不存在/u存在且为黑，旋转+变色
                {
                    //     g
                    //   p   u
                    // c
                    if (cur == parent->_left)
                    {
                        RotateR(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else
                    {
                        //     g
                        //   p   u
                        //     c
                        RotateL(parent);
                        RotateR(grandfather);
                        cur->_col = BLACK;
                        //parent->_col = RED;
                        grandfather->_col = RED;
                    }

                    break;
                }
            }
            else // (grandfather->_right == parent)
            {
                //    g
                //  u   p
                //        c
                Node* uncle = grandfather->_left;
                // 情况1：u存在且为红，变色处理，并继续往上处理
                if (uncle && uncle->_col == RED)
                {
                    parent->_col = BLACK;
                    uncle->_col = BLACK;
                    grandfather->_col = RED;

                    // 继续往上调整
                    cur = grandfather;
                    parent = cur->_parent;
                }
                else // 情况2+3：u不存在/u存在且为黑，旋转+变色
                {
                    //    g
                    //  u   p
                    //        c
                    if (cur == parent->_right)
                    {
                        RotateL(grandfather);
                        grandfather->_col = RED;
                        parent->_col = BLACK;
                    }
                    else
                    {
                        //    g
                        //  u   p
                        //    c
                        RotateR(parent);
                        RotateL(grandfather);
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }

                    break;
                }
            }
        }

        _root->_col = BLACK;

        return make_pair(itertaor(newnode), true);;
    }

    bool IsBalance()
    {
        if (_root && _root->_col == RED)
        {
            cout << "根节点颜色是红色" << endl;
            return false;
        }

        int benchmark = 0;
        Node* cur = _root;
        while (cur)
        {
            if (cur->_col == BLACK)
                ++benchmark;
            cur = cur->_left;
        }

        // 连续红色节点
        return _Check(_root, 0, benchmark);
    }

    int Height()
    {
        return _Height(_root);
    }

private:
    void _Destroy(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }

        _Destroy(root->_left);
        _Destroy(root->_right);
        delete root;
    }

    int _Height(Node* root)
    {
        if (root == NULL)
            return 0;

        int leftH = _Height(root->_left);
        int rightH = _Height(root->_right);

        return leftH > rightH ? leftH + 1 : rightH + 1;
    }

    bool _Check(Node* root, int blackNum, int benchmark)
    {
        if (root == nullptr)
        {
            if (benchmark != blackNum)
            {
                cout << "某条路径黑色节点的数量不相等" << endl;
                return false;
            }

            return true;
        }

        if (root->_col == BLACK)
        {
            ++blackNum;
        }

        if (root->_col == RED
            && root->_parent
            && root->_parent->_col == RED)
        {
            cout << "存在连续的红色节点" << endl;
            return false;
        }

        return _Check(root->_left, blackNum, benchmark)
            && _Check(root->_right, blackNum, benchmark);
    }

    void RotateL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;

        parent->_right = subRL;
        if (subRL)
            subRL->_parent = parent;

        Node* ppnode = parent->_parent;

        subR->_left = parent;
        parent->_parent = subR;

        if (ppnode == nullptr)
        {
            _root = subR;
            _root->_parent = nullptr;
        }
        else
        {
            if (ppnode->_left == parent)
            {
                ppnode->_left = subR;
            }
            else
            {
                ppnode->_right = subR;
            }

            subR->_parent = ppnode;
        }
    }

    void RotateR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        parent->_left = subLR;
        if (subLR)
            subLR->_parent = parent;

        Node* ppnode = parent->_parent;

        subL->_right = parent;
        parent->_parent = subL;

        if (parent == _root)
        {
            _root = subL;
            _root->_parent = nullptr;
        }
        else
        {
            if (ppnode->_left == parent)
            {
                ppnode->_left = subL;
            }
            else
            {
                ppnode->_right = subL;
            }
            subL->_parent = ppnode;
        }
    }

private:
    Node* _root = nullptr;
};



#endif /* RBTree_h */
