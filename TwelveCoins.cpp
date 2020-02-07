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
#include <unistd.h> //linux only
#include "ThreadPool.h"
#include "TwelveCoins.hpp"
#include "Params.hpp"

#define INPUTFILE "input.txt"
#define ANSWERFILE "answer.txt"

/**
 * @brief: Loads the input file into a vector of type int vector. Each line in the file contains 
 *           12 numbers. Each represents a weight of the coins being weighed against each other.
 *           The inner vector contains all 12 int values. The outer vector contains these 12 int
 *           values for each line in the input file.
 *           Example of a line from inputFile: "10 10 2 10 10 10 10 10 10 10 10 10" 
 * 
 * @return:A vector of int vectors, where each value is an int for each weight of the 12 coins in
 *           each line of the input file.
 */
std::vector<std::vector<int>> TwelveCoins::initInput()
{
    std::vector<std::vector<int>> inpVect;

    // Load Input Values
    std::ifstream inpFile(INPUTFILE);
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

/**
 * @brief: Loads the answer file into a vector of type coin. Each coin will contain two ints. An index 
 *           value which is the first number in the line and than a "weight" which is an integer between
 *           0 and 20.
 * 
 * @return:A vector with one coin for each line in the answer file.
 */
std::vector<coin> TwelveCoins::initAnswers()
{
    std::vector<coin> ansVect;

    std::ifstream ansFile(ANSWERFILE);
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

/**
 * @brief: Executes the twelvecoins algorithm upon the input vector which contains 12 
 *           int values. All of them are the same number, apart from one random input that can be
 *           equal to anything between 0 and 20. This provides us with an equally as likely chance
 *           of the odd coin being higher or lower or a slight chance of being all equal.
 *         All outputs are concluded through only three weighings.
 *         Further information can be found at https://en.wikipedia.org/wiki/Balance_puzzle#Twelve-coin_problem
 * 
 * @return:Returned is a new coin type which includes it's index in the input vector and it's weight
 *           Since we can not determine it's actual weight using this algorithm the returned weight is
 *           only a number 1 higher if it is heavier or a number 1 lower if it is lighter than the rest.
 */
coin TwelveCoins::exec(std::vector<int> input) 
{
    coin out;
    // initial initalization
    std::vector<int> one, two;
    one = slice(input,0,3);
    two = slice(input,4,7);

    /* used to delay the algorithm
    * for an algorithm this simple, singlethreading is superior reguardless
    * this slows the algorithm so multithreading is superior */
    usleep(1 * 100);

    int weighOne, weighTwo, weighThree = 0;
    weighOne = weigh(one,two);
    if (weighOne == 0) { // weigh one
        // A == B are not equal, problem ball exists in C
        one = slice(input,0,2);
        two = slice(input,8,10);
        weighTwo = weigh(one,two);
        if (weighTwo == 0) {
            weighThree = weigh(input.at(0),input.at(11));
            if (weighThree == 0)
                out.set(-1,normalWeight); // They are all the same weight
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

/**
 * @brief: Compares our calculated odd coin against the actual odd coin to see if we were correct
 *           about it's index and if its heavier or lighter than the rest.
 * 
 * @return:Returns true or false if our calculated coin is the odd one out (if one exists).
 */
bool TwelveCoins::validate(coin out, coin ans)
{
    if (out.getIndex() == ans.getIndex() && out.getWeight() == ans.getWeight())
        return 1; // true
    std::cout << "out index,weight: " << out.getIndex() << " " << out.getWeight() << " ans index,weight: " << ans.getIndex() << " " << ans.getWeight() << std::endl;
    return 0; // false
}

/**
 * @brief: Creates a new subvector of the vector passed in and the desired index range.
 * 
 * @return:Returns a subvector containing only the index range specified.
 */
std::vector<int> TwelveCoins::slice(std::vector<int> v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<int> vec(first, last);
    return vec;
}

/**
 * @brief: Compares the weights of each side of the scale, a and b, to see which is heavier.
 * 
 * @return:Returns 0 for equal, 1 for a is heavier than b, 2 if a is lighter than b, and 3 if error
 */
int TwelveCoins::weigh(int a, int b)
{
    if (a == b)
        return 0;
    else if (a > b)
        return 1;
    else if (a < b)
        return 2;
    else // error
        return 3;
}

/**
 * @brief: Compares the weights of each side of the scale, a and b, to see which is heavier.
 * 
 * @return:Returns 0 for equal, 1 for a is heavier than b, 2 if a is lighter than b, and 3 if error
 */
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

/**
 * @brief: Computes the sum of all integers in a given vector.
 * 
 * @return:Returns sum of all coins in a given sample vector.
 */
int TwelveCoins::sum(std::vector<int> arr)
{
    int retVal = 0;
    for (int i : arr)
        retVal += i;
    return retVal;
}

/**
 * @brief: Generates an input and answer file. The input file contains 12 numbers all being the same
 *           apart from one which may be any number between 0 and 20. The answer file specifies which
 *           number was different by writing it's index value and it's integer value.
 * 
 * @return:Returns 0 if completed successfully.
 */
int TwelveCoins::generate(int size)
{
    std::ofstream myinput, myanswer;
    myinput.open (INPUTFILE);
    myanswer.open (ANSWERFILE);
    srand(time(NULL));
    myinput << "# Generate input of size: " << size << "\n";
    myanswer << "# Generate answer of size: " << size << "\n";
    for (int i = 0;i < size; i++) {
        int randIndex = -1;
        int randWeight = normalWeight;
        //while (randWeight == normalWeight)
            randWeight = std::rand() % 21; // range from 1 to 20 0,1,2,3,4,5,6,7,8,9 11,12,13,14,15,16,17,18,19,20
        randIndex = std::rand() % 11;
        for (int i = 0; i < 12; i++) {
            if (i == randIndex)
                myinput << randWeight << " ";
            else
                myinput << "10 ";
        }
        myinput << "\n";
        if (randWeight == normalWeight)
            randIndex = -1;
        myanswer << randIndex << " " << randWeight << "\n";
    }
    myinput.close();
    myanswer.close();
    return 0;
}