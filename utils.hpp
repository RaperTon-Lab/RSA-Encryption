#pragma once
#include "rsa.hpp"
#include <algorithm>
#include <string>

bigInt strToAscii(std::string str)
{
    int len;
    bigInt n = 1;
    len = str.length();
    // std::cout << len << std::endl;
    for (int i = 0; i < len; ++i)
    {
        n = n * 1000 + str.at(i);
        // std::cout << n << std::endl;
    }
    return n;
}
std::string asciiToStr(bigInt n)
{
    std::string res;
    int j = 0;
    while (n != 1)
    {
        res.push_back(char(n % 1000));
        ++j;
        n = n / 1000;
    }
    reverse(res.begin(), res.end());
    return res;
}
