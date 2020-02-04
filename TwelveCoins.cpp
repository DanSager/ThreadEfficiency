/**
 * @file: TwelveCoins.cpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> 
#include <stdlib.h>
#include <chrono>
#include <unistd.h> //linux only //remove later
#include "TwelveCoins.hpp"
#include "Params.hpp"

#define inputFile "input.txt"
#define answerFile "answer.txt"

std::vector<std::vector<int>> TwelveCoins::initInput()
{
    std::vector<std::vector<int>> inpVect;

    // Load Input Values
    std::ifstream inpFile(inputFile);
    std::string inpLine;
    while (std::getline(inpFile, inpLine)) {
        if (inpLine[0] == '#') continue;
        if (inpLine[0] == '\n') continue;
        std::stringstream strStream(inpLine);
        std::string temp; 
        std::vector<int> twelveweights; 
        while (!strStream.eof()) { 
            int val = -1;
            strStream >> val;
            if (val != -1)
                twelveweights.push_back(val);
        }
        inpVect.push_back(twelveweights);
    }

    return inpVect;
}

std::vector<coin> TwelveCoins::initAnswers()
{
    std::vector<coin> ansVect;

    std::ifstream ansFile(answerFile);
    std::string ansLine;
    while (std::getline(ansFile, ansLine)) {
        if (ansLine[0] == '#') continue;
        if (ansLine[0] == '\n') continue;
        std::stringstream strStream(ansLine);
        int index;
        int weight;
        strStream >> index >> weight;
        if (weight > normalWeight) weight = heavier;
        else if (weight < normalWeight) weight = lighter;
        ansVect.push_back(coin(index,weight));
    }
    ansFile.close();

    return ansVect;
}

void TwelveCoins::runExec(std::vector<std::vector<int>> inpVect, std::vector<coin> ansVect)
{
    // Execute the algo
    int i = 0;
    int correct = 0;
    int totalLines = 0;
    std::chrono::microseconds duration = std::chrono::milliseconds(0);
    auto startTotal = std::chrono::high_resolution_clock::now();
    for (std::vector<std::vector<int>>::iterator it = inpVect.begin() ; it != inpVect.end(); ++it, ++i) {
        totalLines++;
        std::vector<int> arr = *it;
        auto start = std::chrono::high_resolution_clock::now();
        coin out = exec(arr);
        auto stop = std::chrono::high_resolution_clock::now();
        duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        correct += validate(out,ansVect.at(i));
    }
    auto stopTotal = std::chrono::high_resolution_clock::now();
    auto durationTotal = std::chrono::duration_cast<std::chrono::microseconds>(stopTotal - startTotal);
    std::cout << "Time taken by exec: " << duration.count() << " microseconds" << std::endl;
    std::cout << "Time taken by total: " << durationTotal.count() << " microseconds" << std::endl;
    std::cout << "Correct: " << correct << ", Total: " << totalLines << std::endl;
}

coin TwelveCoins::exec(std::vector<int> input) 
{
    coin out;
    // initial initalization
    std::vector<int> one, two;
    one = slice(input,0,3);
    two = slice(input,4,7);

    sleep(1);

    int weighOne, weighTwo, weighThree = 0;
    weighOne = weigh(one,two);
    if (weighOne == 0) { // weigh one
        // A == B are not equal, problem ball exists in C
        one = slice(input,0,2);
        two = slice(input,8,10);
        weighTwo = weigh(one,two);
        if (weighTwo == 0) {
            weighThree = weigh(input.at(0),input.at(11));
            if (weighThree == 1)
                out.set(11,lighter);
            else if (weighThree == 2)
                out.set(11,heavier);
        } else if (weighTwo == 1) {
            weighThree = weigh(input.at(8),input.at(9));
            if (weighThree == 0)
                out.set(10,lighter);
            else if (weighThree == 1)
                out.set(9,lighter);
            else if (weighThree == 2)
                out.set(8,lighter);
        } else if (weighTwo == 2) {
            weighThree = weigh(input.at(8),input.at(9));
            if (weighThree == 0)
                out.set(10,heavier);
            else if (weighThree == 1)
                out.set(8,heavier);
            else if (weighThree == 2)
                out.set(9,heavier);
        }
    } else if (weighOne == 1) {
        // A > B
        one = {input[0],input[1],input[4]};
        two = {input[5],input[2],input[3]};
        weighTwo = weigh(one,two);
        if (weighTwo == 0) {
            weighThree = weigh(input.at(6),input.at(7));
            if (weighThree == 1)
                out.set(7,lighter);
            else if (weighThree == 2)
                out.set(6,lighter);
        } else if (weighTwo == 1) {
            weighThree = weigh(input.at(0),input.at(1));
            if (weighThree == 0)
                out.set(5,lighter);
            else if (weighThree == 1)
                out.set(0,heavier);
            else if (weighThree == 2)
                out.set(1,heavier);
        } else if (weighTwo == 2) {
            weighThree = weigh(input.at(2),input.at(3));
            if (weighThree == 0)
                out.set(4,lighter);
            else if (weighThree == 1)
                out.set(2,heavier);
            else if (weighThree == 2)
                out.set(3,heavier);
        }
    } else if (weighOne == 2) {
        // A < B
        one = {input[4],input[5],input[0]};
        two = {input[1],input[6],input[7]};
        weighTwo = weigh(one,two);
        if (weighTwo == 0) {
            weighThree = weigh(input.at(2),input.at(3));
            if (weighThree == 1)
                out.set(3,lighter);
            else if (weighThree == 2)
                out.set(2,lighter);
        } else if (weighTwo == 1) {
            weighThree = weigh(input.at(4),input.at(5));
            if (weighThree == 0)
                out.set(1,lighter);
            else if (weighThree == 1)
                out.set(4,heavier);
            else if (weighThree == 2)
                out.set(5,heavier);
        } else if (weighTwo == 2) {
            weighThree = weigh(input.at(6),input.at(7));
            if (weighThree == 0)
                out.set(0,lighter);
            else if (weighThree == 1)
                out.set(6,heavier);
            else if (weighThree == 2)
                out.set(7,heavier);
        }
    }
    
    return out;
}

int TwelveCoins::validate(coin out, coin ans)
{
    if (out.getIndex() == ans.getIndex() && out.getWeight() == ans.getWeight())
        return 1;
    std::cout << "out index,weight: " << out.getIndex() << " " << out.getWeight() << " ans index,weight: " << ans.getIndex() << " " << ans.getWeight() << std::endl;
    return 0;
}

std::vector<int> TwelveCoins::slice(std::vector<int> v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<int> vec(first, last);
    return vec;
}

int TwelveCoins::weigh(int a, int b)
{
    if (a == b)
        return 0;
    else if (a > b)
        return 1;
    else if (a < b)
        return 2;
    else 
        return 3;
}

int TwelveCoins::weigh(std::vector<int> a, std::vector<int> b)
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

int TwelveCoins::sum(std::vector<int> arr)
{
    int retVal = 0;
    for (int i : arr)
        retVal += i;
    return retVal;
}

int TwelveCoins::generate(int size)
{
    std::ofstream myinput, myanswer;
    myinput.open ("input.txt");
    myanswer.open ("answer.txt");
    srand(time(NULL));
    myinput << "# Generate input of size: " << size << "\n";
    myanswer << "# Generate answer of size: " << size << "\n";
    for (int i = 0;i < size; i++) {
        int randIndex = -1;
        int randWeight = normalWeight;
        while (randWeight == normalWeight)
            randWeight = std::rand() % 21; // range from 1 to 20 0,1,2,3,4,5,6,7,8,9 11,12,13,14,15,16,17,18,19,20
        randIndex = std::rand() % 11;
        for (int i = 0; i < 12; i++) {
            if (i == randIndex)
                myinput << randWeight << " ";
            else
                myinput << "10 ";
        }
        myinput << "\n";
        myanswer << randIndex << " " << randWeight << "\n";
    }
    myinput.close();
    myanswer.close();
    return 0;
}