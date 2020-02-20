/**
 * @file: ExecuteMerge.cpp
 * @brief: 
 * 
 * @date: 2/12/2020
 * @author: Dan Sager
 */

#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <Params.hpp>
#include <ExecuteMerge.hpp>
#include "MergeSort.hpp"

MergeSort ms;
std::mutex myLock;
std::vector<int> multiThreadVect;
std::vector<std::vector<int>> sortedVects;

results ExecuteMerge::executeSingle(params p)
{
    results r;

    std::chrono::_V2::system_clock::time_point startFunction, stopFunction, startAlgorithm, stopAlgorithm;
    startFunction = std::chrono::high_resolution_clock::now();

    std::vector<int> v;

    if (p.generateNew)
        v = ms.generateVect(p.count);
    else {
        v = ms.initVect(p.count);
        if (!v.size())
            v = ms.generateVect(p.count);
    }

    int size = v.size();

    startAlgorithm = std::chrono::high_resolution_clock::now();
    v = ms.mergeSort(v);
    stopAlgorithm = std::chrono::high_resolution_clock::now();

    r.correct = ms.validateSorted(v, size);

    stopFunction = std::chrono::high_resolution_clock::now();
    auto durationAlgorithm = std::chrono::duration_cast<std::chrono::microseconds>(stopAlgorithm - startAlgorithm);
    auto durationFunction = std::chrono::duration_cast<std::chrono::microseconds>(stopFunction - startFunction);
    r.algoDuration = durationAlgorithm;
    r.functDuration = durationFunction;

    return r;
}

void execMulit(std::vector<int> v)
{
    v = ms.mergeSort(v);
    myLock.lock();
    sortedVects.push_back(v);
    myLock.unlock();
}

void threadMerge(int i, int incr)
{
    sortedVects.at(i) = ms.merge(sortedVects.at(i),sortedVects.at(i+incr));
}

/*
*   Note: This algorithm is far from optimal and makes very poor use of space.
*         Count * p.threads space complexity to be exact
*/
results ExecuteMerge::executeMulti(params p)
{
    results r;

    std::chrono::_V2::system_clock::time_point startFunction, stopFunction, startAlgorithm, stopAlgorithm;
    startFunction = std::chrono::high_resolution_clock::now();

    std::vector<int> v;

    if (p.generateNew)
        v = ms.generateVect(p.count);
    else {
        v = ms.initVect(p.count);
    }
    
    int size = v.size();

    if (p.count < p.threads)
        p.threads = p.count;

    startAlgorithm = std::chrono::high_resolution_clock::now();

    // Multithread
    std::vector<std::vector<int>> splits(p.threads);

    splits = ms.SplitVector(v,p.threads);
    //std::cout << "splits size: " << splits.size() << std::endl;

    std::vector<std::thread> threads(p.threads);

    // Sort p.threads sized lists individually
    for (int i = 0; i < p.threads; ++i) {
        threads[i] = std::thread(execMulit,splits[i]);
    }

    for (int i = 0; i < p.threads; ++i) {
        threads[i].join();
    }

    int incr = 1;
    int vectorSize = sortedVects.size();

    // Merge the sorted lists back together with multithreading
    while (incr < vectorSize) {
        std::vector<std::thread> t(vectorSize);
        int i = 0;
        int d = 0;
        while (i < vectorSize) {
            if (i + incr >= sortedVects.size())
                break;
            else
                t[d] = std::thread(threadMerge,i,incr);
            i = i + incr*2;
            d++;
        }
        for (int j = 0; j < vectorSize; ++j) {
            if (t[j].joinable())
                t[j].join();
        }
        incr = incr*2;
    }

    stopAlgorithm = std::chrono::high_resolution_clock::now();

    r.correct = ms.validateSorted(sortedVects.at(0),sortedVects.at(0).size());

    stopFunction = std::chrono::high_resolution_clock::now();
    auto durationAlgorithm = std::chrono::duration_cast<std::chrono::microseconds>(stopAlgorithm - startAlgorithm);
    auto durationFunction = std::chrono::duration_cast<std::chrono::microseconds>(stopFunction - startFunction);
    r.algoDuration = durationAlgorithm;
    r.functDuration = durationFunction;

    return r;
}