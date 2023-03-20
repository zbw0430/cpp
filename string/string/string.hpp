//
//  string.hpp
//  string
//
//  Created by 暖暖 on 2023/3/20.
//

#pragma once
#include "iostream"
#include<assert.h>
#include "string"

namespace zbw
{
    class string
    {
    public:
        typedef char* iterator;
        typedef const char* const_iterator;

        iterator begin()
        {
            return _str;
        }

        iterator end()
        {
            return _str + _size;
        }

        const_iterator begin() const
        {
            return _str;
        }

        const_iterator end() const
        {
            return _str + _size;
        }

        
        string(const char* str = "")
            :_size(strlen(str))
        {
            _capacity = _size == 0 ? 3 : _size;
            _str = new char[_capacity + 1];
            strcpy(_str, str);
        }

        // s3(s2)
        string(const string& s)
            :_size(s._size)
            , _capacity(s._capacity)
        {
            _str = new char[s._capacity + 1];
            strcpy(_str, s._str);
        }

        // s1 = s3;
        // s1 = s1;
        string& operator=(const string& s)
        {
            if (this != &s)
            {
                char* tmp = new char[s._capacity + 1];
                strcpy(tmp, s._str);
                delete[] _str;
                _str = tmp;

                _size = s._size;
                _capacity = s._capacity;
            }

            return *this;
        }

        ~string()
        {
            delete[] _str;
            _str = nullptr;
            _size = _capacity = 0;
        }

        const char* c_str()
        {
            return _str;
        }

        const char& operator[](size_t pos) const
        {
            assert(pos < _size);
            return _str[pos];
        }

        char& operator[](size_t pos)
        {
            assert(pos < _size);
            return _str[pos];
        }

        size_t size() const
        {
            return _size;
        }

        size_t capacity() const
        {
            return _capacity;
        }

        // 不修改成员变量数据的函数，最好都加上const
        bool operator>(const string& s) const
        {
            return strcmp(_str, s._str) > 0;
        }

        bool operator==(const string& s) const
        {
            return strcmp(_str, s._str) == 0;
        }

        bool operator>=(const string& s) const
        {
            //return *this > s || *this == s;
            return *this > s || s == *this;
        }

        bool operator<(const string& s) const
        {
            return !(*this >= s);
        }

        bool operator<=(const string& s) const
        {
            return !(*this > s);
        }

        bool operator!=(const string& s) const
        {
            return !(*this == s);
        }

        void resize(size_t n, char ch = '\0')
        {
            if (n < _size)
            {
                // 删除数据--保留前n个
                _size = n;
                _str[_size] = '\0';
            }
            else if (n > _size)
            {
                if (n > _capacity)
                {
                    reserve(n);
                }

                size_t i = _size;
                while (i < n)
                {
                    _str[i] = ch;
                    ++i;
                }

                _size = n;
                _str[_size] = '\0';
            }
        }

        void reserve(size_t n)
        {
            if (n > _capacity)
            {
                char* tmp = new char[n + 1];
                strcpy(tmp, _str);
                delete[] _str;
                _str = tmp;

                _capacity = n;
            }
        }

        void push_back(char ch)
        {
            /*if (_size + 1 > _capacity)
            {
                reserve(_capacity * 2);
            }

            _str[_size] = ch;
            ++_size;

            _str[_size] = '\0';*/
            insert(_size, ch);
        }

        void append(const char* str)
        {
            //size_t len = strlen(str);
            //if (_size+len > _capacity)
            //{
            //    reserve(_size + len);
            //}

            //strcpy(_str + _size, str);
            ////strcat(_str, str);
            //_size += len;
            insert(_size, str);
        }

        string& operator+=(char ch)
        {
            push_back(ch);
            return *this;
        }

        string& operator+=(const char* str)
        {
            append(str);
            return *this;
        }

        string& insert(size_t pos, char ch)
        {
            assert(pos <= _size);
            if (_size + 1 > _capacity)
            {
                reserve(2 * _capacity);
            }

            size_t end = _size + 1;
            while (end > pos)
            {
                _str[end] = _str[end-1];
                --end;
            }

            _str[pos] = ch;
            ++_size;

            return *this;
        }

        string& insert(size_t pos, const char* str)
        {
            assert(pos <= _size);

            size_t len = strlen(str);

            if (_size + len > _capacity)
            {
                reserve(_size + len);
            }

            // 挪动数据
            size_t end = _size + len;
            while (end > pos + len - 1)
            {
                _str[end] = _str[end - len];
                --end;
            }

            // 拷贝插入
            strncpy(_str + pos, str, len);
            _size += len;

            return *this;

        }

        string& erase(size_t pos, size_t len = npos)
        {
            assert(pos < _size);

            if (len == npos || pos + len >= _size)
            {
                _str[pos] = '\0';
                _size = pos;
            }
            else
            {
                strcpy(_str + pos, _str + pos + len);
                _size -= len;
            }

            return *this;
        }

        //swap(s1, s2);
        //s1.swap(s2);
        void swap(string& s)
        {
            std::swap(_str, s._str);
            std::swap(_capacity, s._capacity);
            std::swap(_size, s._size);
        }

        size_t find(char ch, size_t pos = 0)
        {
            assert(pos < _size);

            for (size_t i = pos; i < _size; ++i)
            {
                if (_str[i] == ch)
                {
                    return i;
                }
            }

            return npos;
        }

        size_t find(const char* str, size_t pos = 0)
        {
            assert(pos < _size);

            // kmp
            char* p = strstr(_str + pos, str);
            if (p == nullptr)
            {
                return npos;
            }
            else
            {
                return p - _str;
            }
        }

        void clear()
        {
            _str[0] = '\0';
            _size = 0;
        }
        
    private:
        char* _str;
        size_t _capacity;
        size_t _size;

        static const size_t npos;
    };

    const size_t string::npos = -1;

    std::ostream& operator<<(std::ostream& out, const string& s)
    {
        for (auto ch : s)
        {
            out << ch;
        }
        return out;
    }

    std::istream& operator>>(std::istream& in, string& s)
    {
        s.clear();

        char ch = in.get();
        char buff[128];
        size_t i = 0;
        while (ch != ' ' && ch != '\n')
        {
            buff[i++] = ch;
            if (i == 127)
            {
                buff[127] = '\0';
                s += buff;
                i = 0;
            }

            ch = in.get();
        }

        if (i != 0)
        {
            buff[i] = '\0';
            s += buff;
        }

        return in;
    }

    
}
