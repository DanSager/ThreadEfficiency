/**
 * @file: MergeSort.cpp
 * @brief: 
 * 
 * @date: 2/6/2020
 * @author: Dan Sager
 */

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <mutex>
#include <semaphore.h> //linux only
#include "MergeSort.hpp"

using namespace std;

const int MAX_INT = 65536;
std::mutex myLock;             // prevents updating global variables simulationously
vector<int> multiThreadVect;

vector<int> MergeSort::merge(vector<int> left, vector<int> right)
{
    vector<int> result;
    while ((int)left.size() > 0 || (int)right.size() > 0) {
        if ((int)left.size() > 0 && (int)right.size() > 0) {
            if ((int)left.front() <= (int)right.front()) {
                result.push_back((int)left.front());
                left.erase(left.begin());
            } 
        else {
            result.push_back((int)right.front());
            right.erase(right.begin());
        }
    } else if ((int)left.size() > 0) {
        for (int i = 0; i < (int)left.size(); i++)
            result.push_back(left[i]);
        break;
    } else if ((int)right.size() > 0) {
        for (int i = 0; i < (int)right.size(); i++)
           result.push_back(right[i]);
        break;
        }
    }
    return result;
}

vector<int> MergeSort::slice(vector<int> v, int left, int right)
{
    auto first = v.cbegin() + left;
    auto last = v.cbegin() + right;

    std::vector<int> vec(first, last);
    return vec;
}

vector<int> MergeSort::mSort(vector<int> vect)
{
    int size = (int)vect.size();
    if (size <= 1)
        return vect;

    vector<int> left, right, result;

    int middle = (size+1)/2;

    left = slice(vect,0,middle);
    right = slice(vect,middle,size);

    left = mSort(left);
    right = mSort(right);
    result = merge(left,right);

    return result;
}

vector<int> MergeSort::generateVect(int size)
{
    vector<int> intVect(size);
    srand(time(NULL));
    int i = 0;
    while (i < size) {
        int randInt = rand() % MAX_INT; // can be any 0-65535
        intVect[i] = randInt;
        i++;
    }
    return intVect;
}

bool MergeSort::validateSorted(vector<int> v, int size)
{
    if (v.size() != size)
        return false;
    int previous = 0;
    for (int i : v) {
        if (i < previous)
            return false;
        previous = i;
    }
    return true;
}

void MergeSort::printVect(vector<int> intVect)
{
    for (int i = 0; i < intVect.size(); ++i) cout << intVect[i] << " ";
    cout << "\n";
}

std::vector<std::vector<int>> SplitVector(const std::vector<int>& vec, size_t n)
{
    std::vector<std::vector<int>> outVec;

    size_t length = vec.size() / n;
    size_t remain = vec.size() % n;

    size_t begin = 0;
    size_t end = 0;

    for (size_t i = 0; i < std::min(n, vec.size()); ++i)
    {
        end += (remain > 0) ? (length + !!(remain--)) : length;

        outVec.push_back(std::vector<int>(vec.begin() + begin, vec.begin() + end));

        begin = end;
    }

    return outVec;
}

void execM(vector<int> v)
{
    MergeSort m;
    v = m.mSort(v);
    myLock.lock();
    multiThreadVect = m.merge(multiThreadVect,v);
    myLock.unlock();
}

void MergeSort::execMulti(params p, vector<int> v)
{
    std::cout << "Multithreading" << std::endl;
    vector<vector<int>> splits(p.threads);

    splits = SplitVector(v,p.threads);
    std::cout << "splits size: " << splits.size() << std::endl;

    std::vector<std::thread> threads(p.threads);
    for (int i = 0; i < p.threads; ++i) {
        threads[i] = std::thread(execM,splits[i]);
    }

    for (int i = 0; i < p.threads; ++i) {
        threads[i].join();
    }

    std::cout << "Sorted: " << validateSorted(multiThreadVect,multiThreadVect.size()) << std::endl;
}

void MergeSort::init(params p)
{
    vector<int> v = generateVect(p.buildCount);
    int size = v.size();
    std::chrono::_V2::system_clock::time_point startAlgo, stopAlgo;// = std::chrono::high_resolution_clock::now();
    //printVect(v);
    if (p.threads == 1) {
        startAlgo = std::chrono::high_resolution_clock::now();
        v = mSort(v);
        std::cout << "Sorted: " << validateSorted(v, size) << std::endl;
        stopAlgo = std::chrono::high_resolution_clock::now();
    } else {
        startAlgo = std::chrono::high_resolution_clock::now();
        execMulti(p,v);
        stopAlgo = std::chrono::high_resolution_clock::now();
    }
    //printVect(v);
    auto durationAlgo = std::chrono::duration_cast<std::chrono::microseconds>(stopAlgo - startAlgo);
    std::cout << durationAlgo.count() << " microseconds" << " - Time taken by merge sort algorithm." << std::endl;
    
}

/*
  Notes of optimizations made:
  - Instead of fetching vector size every time, using one variable to store that info reduced execution time
  - Using slice instead of:
        for (int i = 0; i < middle; i++)
            left.push_back(vect[i]);

        for (int i = middle; i < vect.size(); i++) 
            right.push_back(vect[i]);
    Reduced execution time significantly.
  - Using slice's current algo over:
    vector<int> ret;
    for (int i = left; i < right; i++)
        ret.push_back(v.at(i));
    return ret; 
    Reduced execution time significantly.
 
*/