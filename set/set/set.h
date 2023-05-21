//
//  set.h
//  set
//
//  Created by 暖暖 on 2023/5/21.
//

#pragma once

#include "RBTree.h"

namespace zbw
{
    template<class K>
    class set
    {
        struct SetKeyOfT
        {
            const K& operator()(const K& key)
            {
                return key;
            }
        };
    public:
        typedef typename RBTree<K, K, SetKeyOfT>::const_itertaor iterator;
        typedef typename RBTree<K, K, SetKeyOfT>::const_itertaor const_iterator;


        iterator begin()
        {
            return _t.begin();
        }

        iterator end()
        {
            return _t.end();
        }

        pair<iterator, bool> insert(const K& key)
        {
            return _t.Insert(key);
        }
    private:
        RBTree<K, K, SetKeyOfT> _t;
    };

    void test_set1()
    {
        int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
        set<int> s;
        for (auto e : a)
        {
            s.insert(e);
        }

        set<int>::iterator it = s.begin();
        while (it != s.end())
        {
            cout << *it << " ";
            //*it = 1;

            ++it;
        }
        cout << endl;

        for (auto e : s)
        {
            cout << e << " ";
        }
        cout << endl;
    }
}
