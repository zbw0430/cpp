//
//  vector.hpp
//  vector
//
//  Created by 暖暖 on 2023/3/30.
//

#pragma once
#include "iostream"
#include<assert.h>

namespace zbw
{
    template<class T>
    class vector
    {
    public:
        typedef T* iterator;
        typedef const T* const_iterator;

        //vector()
        //    :_start(nullptr)
        //    , _finish(nullptr)
        //    , _end_of_storage(nullptr)
        //{}

        //vector(size_t n, const T& val = T())
        //    : _start(nullptr)
        //    , _finish(nullptr)
        //    , _end_of_storage(nullptr)
        //{
        //    reserve(n);
        //    for (size_t i = 0; i < n; ++i)
        //    {
        //        push_back(val);
        //    }
        //}

        //// [first, last)
        //template <class InputIterator>
        //vector(InputIterator first, InputIterator last)
        //    : _start(nullptr)
        //    , _finish(nullptr)
        //    , _end_of_storage(nullptr)
        //{
        //    while (first != last)
        //    {
        //        push_back(*first);
        //        ++first;
        //    }
        //}

        vector()
        {}

        //vector<int> v(10, 5);
        vector(size_t n, const T& val = T())
        {
            reserve(n);
            for (size_t i = 0; i < n; ++i)
            {
                push_back(val);
            }
        }

        vector(int n, const T& val = T())
        {
            reserve(n);
            for (int i = 0; i < n; ++i)
            {
                push_back(val);
            }
        }

        /*vector(const vector<T>& v)
        {
            reserve(v.capacity());
            for (auto e : v)
            {
                push_back(e);
            }
        }*/

        vector(const vector<T>& v)
        {
            _start = new T[v.capacity()];
            //memcpy(_start, v._start, sizeof(T)*v.size());
            for (size_t i = 0; i < v.size(); ++i)
            {
                _start[i] = v._start[i];
            }

            _finish = _start + v.size();
            _end_of_storage = _start + v.capacity();
        }

        // [first, last)
        template <class InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                push_back(*first);
                ++first;
            }
        }

        ~vector()
        {
            delete[] _start;
            _start = _finish = _end_of_storage = nullptr;
        }

        iterator begin()
        {
            return _start;
        }

        iterator end()
        {
            return _finish;
        }

        const_iterator begin() const
        {
            return _start;
        }

        const_iterator end() const
        {
            return _finish;
        }

        void resize(size_t n, T val = T())
        {
            if (n < size())
            {
                // 删除数据
                _finish = _start + n;
            }
            else
            {
                if (n > capacity())
                    reserve(n);

                while (_finish != _start+n)
                {
                    *_finish = val;
                    ++_finish;
                }
            }
        }

        void reserve(size_t n)
        {
            if (n > capacity())
            {
                size_t sz = size();
                T* tmp = new T[n];
                if (_start)
                {
                    //memcpy(tmp, _start, sizeof(T)*size());
                    for (size_t i = 0; i < sz; ++i)
                    {
                        tmp[i] = _start[i];
                    }
                    delete[] _start;
                }

                _start = tmp;
                _finish = _start + sz;
                _end_of_storage = _start + n;
            }
        }

        void push_back(const T& x)
        {
            if (_finish == _end_of_storage)
            {
                reserve(capacity() == 0 ? 4 : capacity()*2);
            }

            *_finish = x;
            ++_finish;
        }

        void pop_back()
        {
            assert(!empty());

            --_finish;
        }

        iterator insert(iterator pos, const T& val)
        {
            assert(pos >= _start);
            assert(pos <= _finish);

            if (_finish == _end_of_storage)
            {
                size_t len = pos - _start;
                reserve(capacity() == 0 ? 4 : capacity() * 2);

                // 扩容后更新pos，解决pos失效的问题
                pos = _start + len;
            }

            iterator end = _finish-1;
            while (end >= pos)
            {
                *(end + 1) = *end;
                --end;
            }

            *pos = val;
            ++_finish;

            return pos;
        }

        iterator erase(iterator pos)
        {
            assert(pos >= _start);
            assert(pos < _finish);

            iterator start = pos + 1;
            while (start != _finish)
            {
                *(start - 1) = *start;
                ++start;
            }

            --_finish;

            return pos;
        }

        size_t capacity() const
        {
            return _end_of_storage - _start;
        }

        size_t size() const
        {
            return _finish - _start;
        }

        bool empty()
        {
            return _start == _finish;
        }

        T& operator[](size_t pos)
        {
            assert(pos < size());

            return _start[pos];
        }

        const T& operator[](size_t pos) const
        {
            assert(pos < size());

            return _start[pos];
        }

    private:
        iterator _start = nullptr;
        iterator _finish = nullptr;
        iterator _end_of_storage = nullptr;
    };

    void func(const vector<int>& v)
    {
        for (size_t i = 0; i < v.size(); ++i)
        {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;

        vector<int>::const_iterator it = v.begin();
        while (it != v.end())
        {
            std::cout << *it << " ";
            ++it;
        }
        std::cout << std::endl << std::endl;
    }

//    void test_vector1()
//    {
//        vector<int> v1;
//        v1.push_back(1);
//        v1.push_back(2);
//        v1.push_back(3);
//        v1.push_back(4);
//        v1.push_back(5);
//
//        func(v1);
//
//        for (size_t i = 0; i < v1.size(); ++i)
//        {
//            cout << v1[i] << " ";
//        }
//        cout << endl;
//
//        v1.pop_back();
//        v1.pop_back();
//
//        vector<int>::iterator it = v1.begin();
//        while (it != v1.end())
//        {
//            cout << *it << " ";
//            ++it;
//        }
//        cout << endl;
//
//        v1.pop_back();
//        v1.pop_back();
//        v1.pop_back();
//        //v1.pop_back();
//
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        //func(v1);
//    }
//
//    //template<class T>
//    //void f()
//    //{
//    //    T x = T();
//    //    cout << x << endl;
//    //}
//
//    //void test_vector2()
//    //{
//    //    // 内置类型有没有构造函数
//    ///*    int i = int();
//    //    int j = int(1);*/
//
//    //    f<int>();
//    //    f<int*>();
//    //    f<double>();
//    //}
//
//    void test_vector2()
//    {
//        vector<int> v1;
//        v1.push_back(1);
//        v1.push_back(2);
//        v1.push_back(3);
//        v1.push_back(4);
//        v1.push_back(5);
//
//        cout << v1.size() << endl;
//        cout << v1.capacity() << endl;
//
//        v1.resize(10);
//
//        cout << v1.size() << endl;
//        cout << v1.capacity() << endl;
//
//        func(v1);
//
//        v1.resize(3);
//
//        func(v1);
//    }
//
//    void test_vector3()
//    {
//        std::vector<int> v1;
//        v1.push_back(1);
//        v1.push_back(2);
//        v1.push_back(3);
//        v1.push_back(4);
//        //v1.push_back(5);
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        /*v1.insert(v1.begin(), 0);
//        for (auto e : v1)
//        {
//        cout << e << " ";
//        }
//        cout << endl;*/
//
//        auto pos = find(v1.begin(), v1.end(), 3);
//        if (pos != v1.end())
//        {
//            //v1.insert(pos, 30);
//            pos = v1.insert(pos, 30);
//        }
//
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        // insert以后我们认为pos失效了，不能再使用
//        (*pos)++;
//
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//    }
//
//    void test_vector4()
//    {
//        std::vector<int> v1;
//        v1.push_back(1);
//        v1.push_back(2);
//        v1.push_back(3);
//        v1.push_back(4);
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        //auto pos = find(v1.begin(), v1.end(), 2);
//        auto pos = find(v1.begin(), v1.end(), 4);
//        if (pos != v1.end())
//        {
//            v1.erase(pos);
//        }
//
//        (*pos)++;
//
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//    }
//
//    void test_vector5()
//    {
//        bit::vector<int> v1;
//        v1.push_back(10);
//        v1.push_back(2);
//        v1.push_back(3);
//        v1.push_back(4);
//        v1.push_back(5);
//        v1.push_back(50);
//
//        bit::vector<int>::iterator it = v1.begin();
//        while (it != v1.end())
//        {
//            if (*it % 2 == 0)
//            {
//                it = v1.erase(it);
//            }
//            else
//            {
//                ++it;
//            }
//        }
//
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//    }
//
//
//    void test_vector6()
//    {
//        //vector<int> v(10u, 5);
//        vector<int> v1(10, 5);
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        vector<int> v2(v1.begin()+1, v1.end()-1);
//        for (auto e : v2)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        std::string s1("hello");
//        vector<int> v3(s1.begin(), s1.end());
//        for (auto e : v3)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        int a[] = { 100, 10, 2, 20, 30 };
//        vector<int> v4(a, a+3);
//        for (auto e : v4)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        v1.insert(v1.begin(), 10);
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        sort(v1.begin(), v1.end());
//
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//
//        for (auto e : a)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        // 休息10:48继续
//        //sort(a, a+sizeof(a)/sizeof(int));
//    /*    greater<int> g;
//        sort(a, a + sizeof(a) / sizeof(int), g);*/
//
//        sort(a, a + sizeof(a) / sizeof(int), greater<int>());
//
//        for (auto e : a)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//    }
//
//    class Solution {
//    public:
//        vector<vector<int>> generate(int numRows) {
//            vector<vector<int>> vv;
//            vv.resize(numRows, vector<int>());
//            for (size_t i = 0; i < vv.size(); ++i)
//            {
//                vv[i].resize(i + 1, 0);
//                vv[i][0] = vv[i][vv[i].size() - 1] = 1;
//            }
//
//            for (size_t i = 0; i < vv.size(); ++i)
//            {
//                for (size_t j = 0; j < vv[i].size(); ++j)
//                {
//                    if (vv[i][j] == 0)
//                    {
//                        vv[i][j] = vv[i - 1][j] + vv[i - 1][j - 1];
//                    }
//                }
//            }
//
//            return vv;
//        }
//    };
//
//    void test_vector7()
//    {
//        vector<int> v1(10, 5);
//        for (auto e : v1)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        vector<int> v2(v1);
//        for (auto e : v2)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        vector<std::string> v3(3, "111111111111111111111");
//        for (auto e : v3)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        vector<std::string> v4(v3);
//        for (auto e : v4)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        v4.push_back("2222222222222222222");
//        v4.push_back("2222222222222222222");
//        v4.push_back("2222222222222222222");
//        for (auto e : v4)
//        {
//            cout << e << " ";
//        }
//        cout << endl;
//
//        vector<vector<int>> ret = Solution().generate(5);
//        for (size_t i = 0; i < ret.size(); ++i)
//        {
//            for (size_t j = 0; j < ret[i].size(); ++j)
//            {
//                cout << ret[i][j] << " ";
//            }
//            cout << endl;
//        }
//        cout << endl;
//    }
}
