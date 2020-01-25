/**
 * @file: WeighingBalls.hpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#ifndef WeighingBalls_HPP
#define WeighingBalls_HPP

#include <vector>

class WeighingBalls {
public:
    void init();
    std::vector<int> slice(std::vector<int> const &v, int m, int n);
    int weigh(std::vector<int> a, std::vector<int> b);
    int sum(std::vector<int> arr);
};

#endif // WeighingBalls_HPP