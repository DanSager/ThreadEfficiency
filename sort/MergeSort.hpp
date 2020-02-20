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
    std::vector<int> mergeSort(std::vector<int> vect);
    std::vector<int> generateVect(int size);
    std::vector<int> initVect(int size);
    void execMulti(params p, std::vector<int> v);
    results init(params p);
    std::vector<std::vector<int>> SplitVector(const std::vector<int>& vec, size_t n);
    int validateSorted(std::vector<int> v, int size);
private:
    std::vector<int> slice(std::vector<int> v, int left, int right);
    void printVect(std::vector<int>);

    std::string LOGFILE = "./sort/input.txt";
};

#endif // MergeSort_HPP