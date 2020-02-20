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
std::mutex myLock;             // prevents updating global variables simulationously
std::vector<int> multiThreadVect;
std::vector<std::vector<int>> sortedVects;

results ExecuteMerge::executeSingle(params p)
{
    results r;

    std::chrono::_V2::system_clock::time_point startFunction, stopFunction, startAlgorithm, stopAlgorithm;
    startFunction = std::chrono::high_resolution_clock::now();

    std::vector<int> v = ms.generateVect(p.count);
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

void execM(std::vector<int> v)
{
    v = ms.mergeSort(v);
    myLock.lock();
    sortedVects.push_back(v);
    //multiThreadVect = ms.merge(multiThreadVect,v);
    myLock.unlock();
}

std::vector<int> recMerge(std::vector<int> v)
{
    std::vector<int> result;
    if (sortedVects.size() == 0)
        return v;
    else if (sortedVects.size() == 1) {
        std::vector<int> right;
        right = sortedVects.back();
        sortedVects.pop_back();
        result = ms.merge(v,right);
    } else {
        std::vector<int> left, right;
        right = sortedVects.back();
        sortedVects.pop_back();
        left = sortedVects.back();
        sortedVects.pop_back();

        result = ms.merge(v,recMerge(ms.merge(left,right)));
    }

    std::cout << "HERE" << std::endl;
    return result;
}

void recMerge2(int i,int incr)
{
    while (incr != sortedVects.size()) {
        while (i != sortedVects.size()) {
            sortedVects.at(i) = ms.merge(sortedVects.at(i),sortedVects.at(i+incr));
            i = i + incr*2;
        }
        i = 0;
        incr = incr*2;
    }

    return;
}

void threadMerge(int i, int incr)
{
    sortedVects.at(i) = ms.merge(sortedVects.at(i),sortedVects.at(i+incr));
}

results ExecuteMerge::executeMulti(params p)
{
    results r;

    std::chrono::_V2::system_clock::time_point startFunction, stopFunction, startAlgorithm, stopAlgorithm;
    startFunction = std::chrono::high_resolution_clock::now();

    std::vector<int> v = ms.generateVect(p.count);
    int size = v.size();

    startAlgorithm = std::chrono::high_resolution_clock::now();
    //v = ms.mergeSort(v);

    // Multithread
    std::vector<std::vector<int>> splits(p.threads);

    splits = ms.SplitVector(v,p.threads);
    //std::cout << "splits size: " << splits.size() << std::endl;

    std::vector<std::thread> threads(p.threads);
    for (int i = 0; i < p.threads; ++i) {
        threads[i] = std::thread(execM,splits[i]);
    }

    for (int i = 0; i < p.threads; ++i) {
        threads[i].join();
    }

    int incr = 1;
    int vectorSize = sortedVects.size();
    while (incr < vectorSize) {
        std::vector<std::thread> t(vectorSize);
        int i = 0;
        int d = 0;
        while (i < vectorSize) {
            //sortedVects.at(i) = ms.merge(sortedVects.at(i),sortedVects.at(i+incr));
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

    std::vector<int> a;
    //a = recMerge(a);
    //recMerge2(0,1);

    // Multithread

    stopAlgorithm = std::chrono::high_resolution_clock::now();

    r.correct = ms.validateSorted(sortedVects.at(0),sortedVects.at(0).size());
    //r.correct = ms.validateSorted(a,a.size());

    stopFunction = std::chrono::high_resolution_clock::now();
    auto durationAlgorithm = std::chrono::duration_cast<std::chrono::microseconds>(stopAlgorithm - startAlgorithm);
    auto durationFunction = std::chrono::duration_cast<std::chrono::microseconds>(stopFunction - startFunction);
    r.algoDuration = durationAlgorithm;
    r.functDuration = durationFunction;

    return r;
}