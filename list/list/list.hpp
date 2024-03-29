//
//  list.hpp
//  list
//
//  Created by 暖暖 on 2023/4/2.
//

#pragma once
#include "iostream"
#include<assert.h>

namespace zbw
{
    template<class T>
    struct list_node
    {
        list_node<T>* _next;
        list_node<T>* _prev;
        T _data;

        list_node(const T& x = T())
            :_next(nullptr)
            , _prev(nullptr)
            , _data(x)
        {}
    };


    // 1、迭代器要么就是原生指针
    // 2、迭代器要么就是自定义类型对原生指针的封装，模拟指针的行为
    template<class T, class Ref, class Ptr>
    struct __list_iterator
    {
        typedef list_node<T> node;
        typedef __list_iterator<T, Ref, Ptr> self;
        node* _node;

        __list_iterator(node* n)
            :_node(n)
        {}

        Ref operator*()
        {
            return _node->_data;
        }

        Ptr operator->()
        {
            return &_node->_data;
        }

        self& operator++()
        {
            _node = _node->_next;

            return *this;
        }

        self operator++(int)
        {
            self tmp(*this);
            _node = _node->_next;

            return tmp;
        }

        self& operator--()
        {
            _node = _node->_prev;

            return *this;
        }

        self operator--(int)
        {
            self tmp(*this);
            _node = _node->_prev;

            return tmp;
        }

        bool operator!=(const self& s)
        {
            return _node != s._node;
        }

        bool operator==(const self& s)
        {
            return _node == s._node;
        }
    };

    /*template<class T>
    struct __list_const_iterator
    {
        typedef list_node<T> node;
        typedef __list_const_iterator<T> self;
        node* _node;

        __list_const_iterator(node* n)
            :_node(n)
        {}

        const T& operator*()
        {
            return _node->_data;
        }

        self& operator++()
        {
            _node = _node->_next;

            return *this;
        }

        self operator++(int)
        {
            self tmp(*this);
            _node = _node->_next;

            return tmp;
        }

        self& operator--()
        {
            _node = _node->_prev;

            return *this;
        }

        self operator--(int)
        {
            self tmp(*this);
            _node = _node->_prev;

            return tmp;
        }

        bool operator!=(const self& s)
        {
            return _node != s._node;
        }

        bool operator==(const self& s)
        {
            return _node == s._node;
        }
    };*/

    template<class T>
    class list
    {
        typedef list_node<T> node;
    public:
        typedef __list_iterator<T, T&, T*> iterator;
        typedef __list_iterator<T, const T&, const T*> const_iterator;

        //typedef __list_const_iterator<T> const_iterator;

        iterator begin()
        {
            //iterator it(_head->_next);
            //return it;
            return iterator(_head->_next);
        }

        const_iterator begin() const
        {
            return const_iterator(_head->_next);
        }

        iterator end()
        {
            return iterator(_head);
        }

        const_iterator end() const
        {
            //iterator it(_head->_next);
            //return it;
            return const_iterator(_head);
        }

        void empty_init()
        {
            _head = new node;
            _head->_next = _head;
            _head->_prev = _head;
        }

        list()
        {
            empty_init();
        }

        template <class Iterator>
        list(Iterator first, Iterator last)
        {
            empty_init();

            while (first != last)
            {
                push_back(*first);
                ++first;
            }
        }

        // lt2(lt1)
        /*list(const list<T>& lt)
        {
        empty_init();
        for (auto e : lt)
        {
        push_back(e);
        }
        }*/
        void swap(list<T>& tmp)
        {
            std::swap(_head, tmp._head);
        }

        list(const list<T>& lt)
        {
            empty_init();

            list<T> tmp(lt.begin(), lt.end());
            swap(tmp);
        }

        // lt1 = lt3
        list<T>& operator=(list<T> lt)
        {
            swap(lt);
            return *this;
        }

        ~list()
        {
            clear();
            delete _head;
            _head = nullptr;
        }

        void clear()
        {
            iterator it = begin();
            while (it != end())
            {
                //it = erase(it);
                erase(it++);
            }
        }

        void push_back(const T& x)
        {
            /*node* tail = _head->_prev;
            node* new_node = new node(x);

            tail->_next = new_node;
            new_node->_prev = tail;
            new_node->_next = _head;
            _head->_prev = new_node;*/

            insert(end(), x);
        }

        void push_front(const T& x)
        {
            insert(begin(), x);
        }

        void pop_back()
        {
            erase(--end());
        }

        void pop_front()
        {
            erase(begin());
        }

        void insert(iterator pos, const T& x)
        {
            node* cur = pos._node;
            node* prev = cur->_prev;

            node* new_node = new node(x);

            prev->_next = new_node;
            new_node->_prev = prev;
            new_node->_next = cur;
            cur->_prev = new_node;
        }

        iterator erase(iterator pos)
        {
            assert(pos != end());

            node* prev = pos._node->_prev;
            node* next = pos._node->_next;

            prev->_next = next;
            next->_prev = prev;
            delete pos._node;

            return iterator(next);
        }
    private:
        node* _head;
    };

    void print_list(const list<int>& lt)
    {
        list<int>::const_iterator it = lt.begin();
        while (it != lt.end())
        {
            //(*it) *= 2;
            std::cout << *it << " ";
            ++it;
        }
        std::cout << std::endl;
    }

//    void test_list1()
//    {
//        const list<int> lt1;
//        const int n = 10;
//        //n = 11;
//
//        list<int> lt;
//        lt.push_back(1);
//        lt.push_back(2);
//        lt.push_back(3);
//        lt.push_back(4);
//
//        // int*
//        list<int>::iterator it = lt.begin();
//        while (it != lt.end())
//        {
//            (*it) *= 2;
//            cout << *it << " ";
//            ++it;
//        }
//        cout << endl;
//
//        for (auto e : lt)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        print_list(lt);
//    }
//
//    struct AA
//    {
//        int _a1;
//        int _a2;
//
//        AA(int a1 = 0, int a2 = 0)
//            :_a1(a1)
//            , _a2(a2)
//        {}
//    };
//
//    void test_list2()
//    {
//        list<AA> lt;
//        lt.push_back(AA(1, 1));
//        lt.push_back(AA(2, 2));
//        lt.push_back(AA(3, 3));
//
//        // AA* ptr
//        list<AA>::iterator it = lt.begin();
//        while (it != lt.end())
//        {
//            //cout << (*it)._a1 << ":" << (*it)._a2 << endl;
//            cout << it->_a1 << ":" << it->_a2 << endl;
//            //cout << it.operator->()->_a1 << ":" << it.operator->()->_a1 << endl;
//            ++it;
//        }
//        cout << endl;
//    }
//
//    void test_list3()
//    {
//        list<int> lt;
//        lt.push_back(1);
//        lt.push_back(2);
//        lt.push_back(3);
//        lt.push_back(4);
//
//        for (auto e : lt)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        auto pos = lt.begin();
//        ++pos;
//        lt.insert(pos, 20);
//
//        for (auto e : lt)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        lt.push_back(100);
//        lt.push_front(1000);
//
//        for (auto e : lt)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        lt.pop_back();
//        lt.pop_front();
//
//        for (auto e : lt)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//    }
//
//    void test_list4()
//    {
//        list<int> lt;
//        lt.push_back(1);
//        lt.push_back(2);
//        lt.push_back(3);
//        lt.push_back(4);
//
//        for (auto e : lt)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        lt.clear();
//
//        for (auto e : lt)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        lt.push_back(10);
//        lt.push_back(2);
//        lt.push_back(3);
//        lt.push_back(40);
//
//        for (auto e : lt)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//    }
//
//    void test_list5()
//    {
//        list<int> lt;
//        lt.push_back(1);
//        lt.push_back(2);
//        lt.push_back(3);
//        lt.push_back(4);
//        lt.push_back(5);
//
//        for (auto e : lt)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        list<int> lt2(lt);
//
//        for (auto e : lt2)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        list<int> lt3;
//        lt3.push_back(10);
//        lt3.push_back(20);
//        lt3.push_back(30);
//
//        for (auto e : lt3)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        lt2 = lt3;
//
//        for (auto e : lt2)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        for (auto e : lt3)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//    }
}
