/**
 * @file: ExecuteSingle.cpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#include <iostream>
#include <chrono>
#include "ExecuteSingle.hpp"
#include "TwelveCoins.hpp"

void ExecuteSingle::Initalize(params p)
{
    if (p.algoName == coins) {
        TwelveCoins coins;
        coins.generate(1000000);
        coins.init();
    }
    else 
        std::cout << "this hasn't been coded yet\n\n";
}