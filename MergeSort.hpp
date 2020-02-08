/**
 * @file: MergeSort.hpp
 * @brief: 
 * 
 * @date: 2/6/2020
 * @author: Dan Sager
 */

#ifndef MergeSort_HPP
#define MergeSort_HPP

#include <vector>
#include "Params.hpp"

class MergeSort {
public:
    std::vector<int> merge(std::vector<int> left, std::vector<int> right);
    std::vector<int> mSort(std::vector<int> vect);
    std::vector<int> generateVect(int size);
    void execMulti(params p, std::vector<int> v);
    void init(params p);
private:
    std::vector<int> slice(std::vector<int> v, int left, int right);
    bool validateSorted(std::vector<int> v, int size);
    void printVect(std::vector<int>);
};

#endif // MergeSort_HPP