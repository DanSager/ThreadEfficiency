/**
 * @file: Execute.hpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#ifndef Execute_HPP
#define Execute_HPP

#include <vector>
#include "TwelveCoins.hpp"
#include "Params.hpp"

struct args {
    std::vector<int> arr;
    coin ans;
};

class Execute {
public:
    void initalizeSingle(params p);
    void initalizeMulti(params p);
    //void execMulti(std::vector<int> arr, coin ans, int &correct, int &totalLines);
    //void *execMulti(void *input);
};

#endif // Execute_HPP