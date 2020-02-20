/**
 * @file: MergeSort.cpp
 * @brief: 
 * 
 * @date: 2/6/2020
 * @author: Dan Sager
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <semaphore.h> //linux only
#include "MergeSort.hpp"

const int MAX_INT = 65536;

std::vector<int> MergeSort::merge(std::vector<int> left, std::vector<int> right)
{
    std::vector<int> result;
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

std::vector<int> MergeSort::slice(std::vector<int> v, int left, int right)
{
    auto first = v.cbegin() + left;
    auto last = v.cbegin() + right;

    std::vector<int> vec(first, last);
    return vec;
}

std::vector<int> MergeSort::mergeSort(std::vector<int> vect)
{
    int size = (int)vect.size();
    if (size <= 1)
        return vect;

    std::vector<int> left, right, result;

    int middle = (size+1)/2;

    left = slice(vect,0,middle);
    right = slice(vect,middle,size);

    left = mergeSort(left);
    right = mergeSort(right);
    result = merge(left,right);

    return result;
}

std::vector<int> MergeSort::generateVect(int size)
{
    std::ofstream log;
    log.open(LOGFILE);
    log << "# Generate input of size: " << size << "\n";

    std::vector<int> intVect(size);
    srand(time(NULL));
    int i = 0;
    while (i < size) {
        int randInt = rand() % MAX_INT; // can be any 0-65535
        intVect[i] = randInt;
        i++;

        log << randInt << " ";
    }
    log.close();
    return intVect;
}

std::vector<int> MergeSort::initVect(int size)
{
    std::vector<int> inpVect;

    // Load Input Values
    std::ifstream inpFile(LOGFILE);
    std::string inpLine;
    while (std::getline(inpFile, inpLine)) {
        if (inpLine[0] == '#') continue;
        if (inpLine[0] == '\n') continue;
        std::stringstream strStream(inpLine);
        std::string temp;
        int num = 0;
        while (!strStream.eof() && num < size) { 
            int val = -1;
            strStream >> val;
            if (val != -1)
                inpVect.push_back(val);
            num++;
        }
    }

    return inpVect;
}

int MergeSort::validateSorted(std::vector<int> v, int size)
{
    int correctlySortedWithoutIssue = 0, previous = 0;
    if (v.size() != size)
        return correctlySortedWithoutIssue;
    for (int i : v) {
        if (i < previous)
            return correctlySortedWithoutIssue;
        previous = i;
        correctlySortedWithoutIssue++;
    }
    return correctlySortedWithoutIssue;
}

void MergeSort::printVect(std::vector<int> intVect)
{
    for (int i = 0; i < intVect.size(); ++i) std::cout << intVect[i] << " ";
    std::cout << "\n";
}

std::vector<std::vector<int>> MergeSort::SplitVector(const std::vector<int>& vec, size_t n)
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