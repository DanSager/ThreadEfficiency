/**
 * @file: Params.hpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#ifndef Params_HPP
#define Params_HPP

enum algo {none, coins, merge};

struct params {
    algo algoName = none;
    int threads = 1;
    bool threadpool = false;
    int buildCount = 0;
    bool generateNew = false;
};

#endif // Params_HPP