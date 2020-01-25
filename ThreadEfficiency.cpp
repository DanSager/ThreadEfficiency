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
#include "ExecuteSingle.hpp"

params p;

int main(int argc, char *argv[])
{
    int retVal = readCommandParams(argc, argv);

    if (retVal == 1)
        exit(1);

    if (p.threads == 1) {
        ExecuteSingle es;
        es.Initalize(p);
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
            if (key == "novalid")
                p.validate = false;
        } else { // value
            value = argv[i];
            if (key != "") {
                if (key == "algo") {
                    if (value == "12balls")
                        p.algoName = balls;
                    else if (value == "floors")
                        p.algoName = floors;
                    else 
                        p.algoName = none;
                }
                else if (key == "threads") {
                    int threads = std::stoi(value);
                    if (threads > 1 && threads < 13)
                        p.threads = threads;
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
        << "./ThreadEfficiency -algo <string> [-threads <n>] [-threadpool] [<-novalid]\n\n"
        << "-algo : specify the algorithm to be used.\n"
        << "-threads : specify the amount of threads to be used. Default = 1\n"
        << "-threadpool : bool value if we should execute using a threadpool or not.\n"
        << "-novalid : bool value if we should validate the output.\n"
        << std::endl;
}

int printParams()
{
    std::cout << "Launch params: ";
    std::cout << "algoName =" << p.algoName << ", ";
    std::cout << "threads =" << p.threads << ", ";
    std::cout << "threadpool =" << p.threadpool << ", ";
    std::cout << "validate =" << p.validate << std::endl;
    return 0;
}