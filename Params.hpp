/**
 * @file: Params.hpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#ifndef Params_HPP
#define Params_HPP

#include <chrono>

const std::string VERSION_NUM = "0.5";
const std::string COINSINPUTFILE = "./coins/inputs.txt";
const std::string COINSANSWERFILE = "./coins/answers.txt";

enum algo {none, coins, merge, mergeMulti};

struct params {
    algo algoName = none;
    int threads = 1;
    int count = 0;
    bool threadpool = false;
    bool generateNew = false;
};

struct results {
    int correct = 0;
    std::chrono::microseconds functDuration = std::chrono::milliseconds(0);
    std::chrono::microseconds algoDuration = std::chrono::milliseconds(0);
};

#endif // Params_HPP