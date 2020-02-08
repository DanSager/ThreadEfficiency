/**
 * @file: ThreadEfficiency.cpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#include <iostream>
#include "ThreadEfficiency.hpp"
#include "Params.hpp"
#include "ExecuteCoins.hpp"
#include "MergeSort.hpp"

params p;

int main(int argc, char *argv[])
{
    int retVal = readCommandParams(argc, argv);

    if (retVal == 1)
        exit(1);

    if (p.algoName == coins) {
        ExecuteCoins ec;
        if (p.threads == 1) {
            ec.initializeSingle(p);
        } else if (p.threads > 1 && p.threads < 13 && p.threadpool == false) {
            ec.initializeMulti(p);
        } else if (p.threads > 1 && p.threads < 13 && p.threadpool == true) {
            ec.initializePool(p);
        }
    } else if (p.algoName == merge) {
        MergeSort ms;
        ms.init(p);
    }

    return 0;
}

int readCommandParams(int argc, char *argv[])
{
    if (argc == 0) { // display default message
        printParamSettings();
        return 1;
    }
    std::string key, value = "";
    for (int i = 1; i<argc;i++) {
        if (argv[i][0] == '-') { // key
            key = &argv[i][1];
            if (key == "threadpool")
                p.threadpool = true;
            else if (key == "generate")
                p.generateNew = true;
        } else { // value
            value = argv[i];
            if (key != "") {
                if (key == "algo") {
                    if (value == "coins")
                        p.algoName = coins;
                    else if (value == "merge")
                        p.algoName = merge;
                    else
                        p.algoName = none;
                }
                else if (key == "threads") {
                    int threads = std::stoi(value);
                    if (threads > 1 && threads < 13)
                        p.threads = threads;
                }
                else if (key == "count") {
                    int count = std::stoi(value);
                    if (count > 0 && count < 999999999)
                        p.buildCount = count;
                }
            }
            key,value = "";
        }
    }
    if (p.algoName == none) {
        printParamSettings();
        return 1;
    }

    printParams();
    return 0;
}

void printParamSettings()
{
    std::cout
        << "Launching ThreadEfficiency Commands\n"
        << "./ThreadEfficiency -algo <string> -count <n> [-threads <n>] [-threadpool] [<-generate]\n\n"
        << "-algo : specify the algorithm to be used.\n"
        << "-count : specify the number of times to execute the algo.\n"
        << "-threads : specify the amount of threads to be used. Default = 1\n"
        << "-threadpool : bool value if we should execute using a threadpool or not.\n"
        << "-generate : bool value if we should generate new inputs or use existing input values\n"
        << std::endl;
}

int printParams()
{
    std::cout << "Launch params: ";
    std::cout << "algoName =" << p.algoName << ", ";
    std::cout << "count =" << p.buildCount << ", ";
    std::cout << "threads =" << p.threads << ", ";
    std::cout << "threadpool =" << p.threadpool << ", ";
    std::cout << "generate =" << p.generateNew << "\n";
    return 0;
}