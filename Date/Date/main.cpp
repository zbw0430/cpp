//
//  main.cpp
//  Date
//
//  Created by 暖暖 on 2023/3/4.
//

#include "Date.hpp"

void test()
{
    Date d1(2020, 1, 1);
    Date d2(2023, 1, 1);
    
    d1 += 100;
    //d1.print();
    cout << d1;
}

int main()
{
    test();
    return 0;
}
