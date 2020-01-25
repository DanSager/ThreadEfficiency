/**
 * @file: ExecuteSingle.cpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#include <iostream>
#include "ExecuteSingle.hpp"
#include "WeighingBalls.hpp"

void ExecuteSingle::Initalize(params p)
{
    if (p.algoName == balls) {
        WeighingBalls wb;
        wb.init();
    }
    else 
        std::cout << "this hasn't been coded yet\n\n";
}