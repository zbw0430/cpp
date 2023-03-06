//
//  Date.hpp
//  Date
//
//  Created by 暖暖 on 2023/3/4.
//

#ifndef Date_hpp
#define Date_hpp

#include <iostream>
#include "assert.h"
using namespace std;

class Date
{
public:
    Date(int year = 2023, int month = 1, int day = 1);
    void print();
    int GetMonthDay(int year, int month);
    
    bool operator==(const Date& d);
    bool operator!=(const Date& d);
    bool operator<(const Date& d);
    bool operator<=(const Date& d);
    bool operator>(const Date& d);
    bool operator>=(const Date& d);
    
    Date& operator+=(int day);
    Date operator+(int day);
    
    // d1 - 100
    Date& operator-=(int day);
    Date operator-(int day);

    // d1 - d2;
    int operator-(const Date& d);

    // ++d1
    Date& operator++();

    // d1++
    Date operator++(int);
    
    Date& operator--();
    Date operator--(int);
    
private:
    int _year;
    int _month;
    int _day;
};

#endif /* Date_hpp */
