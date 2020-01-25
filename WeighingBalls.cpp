/**
 * @file: WeighingBalls.cpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#include <iostream>
#include <vector>
#include "WeighingBalls.hpp"

int sample[12] = {5,5,5,5,7,5,5,5,5,5,5,5};
std::vector<int> samp = {5,5,5,5,5,5,5,5,5,5,5,5};

void WeighingBalls::init() 
{
    // initial initalization
    std::vector<int> a,b,c, one, two;
    a = slice(samp,0,3);
    b = slice(samp,4,7);
    c = slice(samp,8,11);

    int weighOne, weighTwo, weighThree = 0;
    weighOne = weigh(a,b);
    if (weighOne == 0) { // weigh one
        // A == B are not equal, problem ball exists in C
        one = slice(samp,0,2);
        two = slice(samp,8,10);
        weighTwo = weigh(one,two);
        if (weighTwo == 0) {
            one = slice(samp,0,0);
            two = slice(samp,11,11);
            weighThree = weigh(one,two);
            if (weighThree == 1)
                std::cout << "A: ball 12 is lighter\n\n";
            else if (weighThree == 2)
                std::cout << "A: ball 12 is heavier\n\n";
        } else if (weighTwo == 1) {
            one = slice(samp,8,8);
            two = slice(samp,9,9);
            weighThree = weigh(one,two);
            if (weighThree == 0)
                std::cout << "A: ball 11 is lighter\n\n";
            else if (weighThree == 1)
                std::cout << "A: ball 10 is lighter\n\n";
            else if (weighThree == 2)
                std::cout << "A: ball 9 is lighter\n\n";
        } else if (weighTwo == 2) {
            one = slice(samp,8,8);
            two = slice(samp,9,9);
            weighThree = weigh(one,two);
            if (weighThree == 0)
                std::cout << "A: ball 11 is heavier\n\n";
            else if (weighThree == 1)
                std::cout << "A: ball 9 is heavier\n\n";
            else if (weighThree == 2)
                std::cout << "A: ball 10 is heavier\n\n";
        }
    } else if (weighOne == 1) {
        // A > B
        one = {samp[0],samp[1],samp[4]};
        two = {samp[5],samp[2],samp[3]};
        weighTwo = weigh(one,two);
        if (weighTwo == 0) {
            one = slice(samp,6,6);
            two = slice(samp,7,7);
            weighThree = weigh(one,two);
            if (weighThree == 1)
                std::cout << "A: ball 8 is lighter\n\n";
            else if (weighThree == 2)
                std::cout << "A: ball 7 is lighter\n\n";
        } else if (weighTwo == 1) {
            one = slice(samp,0,0);
            two = slice(samp,1,1);
            weighThree = weigh(one,two);
            if (weighThree == 0)
                std::cout << "A: ball 6 is lighter\n\n";
            else if (weighThree == 1)
                std::cout << "A: ball 1 is heavier\n\n";
            else if (weighThree == 2)
                std::cout << "A: ball 2 is heavier\n\n";
        } else if (weighTwo == 2) {
            one = slice(samp,2,2);
            two = slice(samp,3,3);
            weighThree = weigh(one,two);
            if (weighThree == 0)
                std::cout << "A: ball 5 is lighter\n\n";
            else if (weighThree == 1)
                std::cout << "A: ball 3 is heavier\n\n";
            else if (weighThree == 2)
                std::cout << "A: ball 4 is heavier\n\n";
        }
    } else if (weighOne == 2) {
        // A < B
        one = {samp[4],samp[5],samp[0]};
        two = {samp[1],samp[6],samp[7]};
        weighTwo = weigh(one,two);
        if (weighTwo == 0) {
            one = slice(samp,2,2);
            two = slice(samp,3,3);
            weighThree = weigh(one,two);
            if (weighThree == 1)
                std::cout << "A: ball 4 is lighter\n\n";
            else if (weighThree == 2)
                std::cout << "A: ball 3 is lighter\n\n";
        } else if (weighTwo == 1) {
            one = slice(samp,4,4);
            two = slice(samp,5,5);
            weighThree = weigh(one,two);
            if (weighThree == 0)
                std::cout << "A: ball 2 is lighter\n\n";
            else if (weighThree == 1)
                std::cout << "A: ball 5 is heavier\n\n";
            else if (weighThree == 2)
                std::cout << "A: ball 6 is heavier\n\n";
        } else if (weighTwo == 2) {
            one = slice(samp,6,6);
            two = slice(samp,7,7);
            weighThree = weigh(one,two);
            if (weighThree == 0)
                std::cout << "A: ball 1 is lighter\n\n";
            else if (weighThree == 1)
                std::cout << "A: ball 7 is heavier\n\n";
            else if (weighThree == 2)
                std::cout << "A: ball 8 is heavier\n\n";
        }
    }
}

std::vector<int> WeighingBalls::slice(std::vector<int> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<int> vec(first, last);
    return vec;
}

int WeighingBalls::weigh(std::vector<int> a, std::vector<int> b)
{
    int sumA, sumB = 0;
    sumA = sum(a);
    sumB = sum(b);
    if (sumA == sumB) {//odd ball in c
        return 0;
    } else if (sumA > sumB) {
        return 1;
    } else if (sumA < sumB) {
        return 2;
    } else {
        std::cout << "ERROR: WeighingBalls::weigh\n";
        return 3;
    }
}

int WeighingBalls::sum(std::vector<int> arr)
{
    int retVal = 0;
    for (int i : arr)
        retVal += i;
    return retVal;
}