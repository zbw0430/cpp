//
//  AVLTree.h
//  set
//
//  Created by 暖暖 on 2023/5/21.
//

#ifndef AVLTree_h
#define AVLTree_h

#pragma once
#include <assert.h>
#include <time.h>

template<class K, class V>
struct AVLTreeNode
{
    AVLTreeNode<K, V>* _left;
    AVLTreeNode<K, V>* _right;
    AVLTreeNode<K, V>* _parent;
    pair<K, V> _kv;
    int _bf; // balance factor

    AVLTreeNode(const pair<K, V>& kv)
        :_left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)
        , _kv(kv)
        , _bf(0)
    {}
};

template<class K, class V>
class AVLTree
{
    typedef AVLTreeNode<K, V> Node;
public:
    bool Insert(const pair<K, V>& kv)
    {
        if (_root == nullptr)
        {
            _root = new Node(kv);
            return true;
        }

        Node* parent = nullptr;
        Node* cur = _root;
        while (cur)
        {
            if (cur->_kv.first < kv.first)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_kv.first > kv.first)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                return false;
            }
        }

        cur = new Node(kv);
        if (parent->_kv.first > kv.first)
        {
            parent->_left = cur;
        }
        else
        {
            parent->_right = cur;
        }
        cur->_parent = parent;

        // 更新平衡因子
        while (parent)
        {
            if (cur == parent->_right)
            {
                parent->_bf++;
            }
            else
            {
                parent->_bf--;
            }

            if (parent->_bf == 1 || parent->_bf == -1)
            {
                // 继续更新
                parent = parent->_parent;
                cur = cur->_parent;
            }
            else if (parent->_bf == 0)
            {
                break;
            }
            else if (parent->_bf == 2 || parent->_bf == -2)
            {
                // 需要旋转处理 -- 1、让这颗子树平衡 2、降低这颗子树的高度
                if (parent->_bf == 2 && cur->_bf == 1)
                {
                    RotateL(parent);
                }
                else if (parent->_bf == -2 && cur->_bf == -1)
                {
                    RotateR(parent);
                }
                else if (parent->_bf == -2 && cur->_bf == 1)
                {
                    RotateLR(parent);
                }
                else if (parent->_bf == 2 && cur->_bf == -1)
                {
                    RotateRL(parent);
                }
                else
                {
                    assert(false);
                }

                break;
            }
            else
            {
                assert(false);
            }
        }

        return true;
    }

    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

    bool IsBalance()
    {
        return _IsBalance(_root);
    }

    int Height()
    {
        return _Height(_root);
    }

private:
    int _Height(Node* root)
    {
        if (root == NULL)
            return 0;

        int leftH = _Height(root->_left);
        int rightH = _Height(root->_right);

        return leftH > rightH ? leftH + 1 : rightH + 1;
    }

    bool _IsBalance(Node* root)
    {
        if (root == NULL)
        {
            return true;
        }

        int leftH = _Height(root->_left);
        int rightH = _Height(root->_right);

        if (rightH - leftH != root->_bf)
        {
            cout << root->_kv.first << "节点平衡因子异常" << endl;
            return false;
        }

        return abs(leftH - rightH) < 2
            && _IsBalance(root->_left)
            && _IsBalance(root->_right);
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

        parent->_bf = subR->_bf = 0;
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

        subL->_bf = parent->_bf = 0;
    }

    void RotateLR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        int bf = subLR->_bf;

        RotateL(parent->_left);
        RotateR(parent);

        if (bf == 1)
        {
            parent->_bf = 0;
            subLR->_bf = 0;
            subL->_bf = -1;
        }
        else if (bf == -1)
        {
            parent->_bf = 1;
            subLR->_bf = 0;
            subL->_bf = 0;
        }
        else if (bf == 0)
        {
            parent->_bf = 0;
            subLR->_bf = 0;
            subL->_bf = 0;
        }
        else
        {
            assert(false);
        }
    }

    void RotateRL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;
        int bf = subRL->_bf;

        RotateR(parent->_right);
        RotateL(parent);

        if (bf == 1)
        {
            subR->_bf = 0;
            parent->_bf = -1;
            subRL->_bf = 0;
        }
        else if (bf == -1)
        {
            subR->_bf = 1;
            parent->_bf = 0;
            subRL->_bf = 0;
        }
        else if (bf == 0)
        {
            subR->_bf = 0;
            parent->_bf = 0;
            subRL->_bf = 0;
        }
        else
        {
            assert(false);
        }
    }

    void _InOrder(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }

        _InOrder(root->_left);
        cout << root->_kv.first << " ";
        _InOrder(root->_right);
    }
private:
    Node* _root = nullptr;
};

void Test_AVLTree1()
{
    //int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
    int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
    AVLTree<int, int> t1;
    for (auto e : a)
    {
        /*    if (e == 14)
            {
            int x = 0;
            }*/

        t1.Insert(make_pair(e, e));
        cout <<e<<"插入："<<t1.IsBalance() << endl;
    }

    t1.InOrder();
    cout << t1.IsBalance() << endl;
}


void Test_AVLTree2()
{
    srand(time(0));
    const size_t N = 5000000;
    AVLTree<int, int> t;
    for (size_t i = 0; i < N; ++i)
    {
        size_t x = rand() + i;
        t.Insert(make_pair(x, x));
        //cout << t.IsBalance() << endl;
    }

    //t.Inorder();

    cout << t.IsBalance() << endl;
    cout << t.Height() << endl;
}



#endif /* AVLTree_h */
