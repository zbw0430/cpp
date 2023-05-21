//
//  map.h
//  set
//
//  Created by 暖暖 on 2023/5/21.
//

#pragma once

#include "RBTree.h"

namespace zbw
{
    template<class K, class V>
    class map
    {
        struct MapKeyOfT
        {
            const K& operator()(const pair<const K, V>& kv)
            {
                return kv.first;
            }
        };
    public:
        typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::itertaor iterator;

        iterator begin()
        {
            return _t.begin();
        }

        iterator end()
        {
            return _t.end();
        }

        V& operator[](const K& key)
        {
            pair<iterator, bool> ret = _t.Insert(make_pair(key, V()));
            return ret.first->second;
        }

        pair<iterator, bool> insert(const pair<const K, V>& kv)
        {
            return _t.Insert(kv);
        }
    private:
        RBTree<K, pair<const K, V>, MapKeyOfT> _t;
    };

    void test_map1()
    {
        map<string, string> dict;
        dict.insert(make_pair("sort", ""));
        dict.insert(make_pair("string", "ַ"));
        dict.insert(make_pair("count", ""));
        dict.insert(make_pair("string", "(ַ)")); // ʧ

        map<string, string>::iterator it = dict.begin();
        while (it != dict.end())
        {
            cout << it->first << ":" << it->second << endl;
            /*it->first = "1111";
            it->second = "111";*/

            ++it;
        }
        cout << endl;

        for (auto& kv : dict)
        {
            cout << kv.first << ":" << kv.second << endl;
        }
        cout << endl;
    }

    void test_map2()
    {
        string arr[] = { "", "", "ƻ", "", "ƻ", "ƻ", "", "ƻ", "㽶", "ƻ", "㽶", "", "", "" };
        map<string, int> countMap;
        for (auto& e : arr)
        {
            countMap[e]++;
        }
    
        for (auto& kv : countMap)
        {
            cout << kv.first << ":" << kv.second << endl;
        }
    }
}

