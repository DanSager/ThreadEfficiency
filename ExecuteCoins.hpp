/**
 * @file: ExecuteCoins.hpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#ifndef ExecuteCoins_HPP
#define ExecuteCoins_HPP

#include <vector>
#include "TwelveCoins.hpp"
#include "Params.hpp"

class ExecuteCoins {
public:
    void initializeSingle(params p);
    void initializeMulti(params p);
    void initializePool(params p);

private:
    void printStats(int numTotal);
};

#endif // ExecuteCoins_HPP