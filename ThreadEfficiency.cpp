/**
 * @file: ThreadEfficiency.cpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#include <chrono>
#include <iostream>
#include <fstream>
#include "ExecuteCoins.hpp"
#include "ExecuteMerge.hpp"
#include "ThreadEfficiency.hpp"

int main(int argc, char *argv[])
{
    params p;
    results r;
    
    std::string algoname = "";

    int retVal = readCommandParams(p, argc, argv, algoname);
    printParams(p, std::cout);

    if (retVal == 1)
        exit(1);

    if (p.algoName == coins) {
        ExecuteCoins ec;
        if (p.threads == 1) {
            r = ec.initializeSingle(p);
        } else if (p.threads > 1 && p.threads < 13 && p.threadpool == false) {
            r = ec.initializeMulti(p);
        } else if (p.threads > 1 && p.threads < 13 && p.threadpool == true) {
            r = ec.initializePool(p);
        }
    } else if (p.algoName == merge) {
        ExecuteMerge em;
        if (p.threads == 1)
            r = em.executeSingle(p);
        else if (p.threads > 1 )//&& p.threads < 13)
            r = em.executeMulti(p);
    }

    printStats(p, r,std::cout);
    std::string logFile = "log-" + algoname + ".txt";
    std::ofstream log(logFile, std::ios::app);
    printParams(p, log);
    printStats(p, r,log);
    log.close();
    
    return 0;
    
}

int readCommandParams(params& p, int argc, char *argv[], std::string& algoname)
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
                    else if (value == "mergeMulti")
                        p.algoName = mergeMulti;
                    else
                        p.algoName = none;

                    algoname = value;
                }
                else if (key == "threads") {
                    int threads = std::stoi(value);
                    if (threads > 1 )//&& threads < 13)
                        p.threads = threads;
                }
                else if (key == "count") {
                    int count = std::stoi(value);
                    if (count > 0 && count < 999999999)
                        p.count = count;
                }
            }
            key,value = "";
        }
    }
    if (p.algoName == none) {
        printParamSettings();
        return 1;
    }
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

int printParams(params& p, std::ostream& os)
{
    auto time = std::chrono::system_clock::now();
    std::time_t now = std::chrono::system_clock::to_time_t(time);
    os << "Executing v" << VERSION_NUM << " at " << std::ctime(&now);
    os  << "Parameters: "
        << "algo = " << p.algoName << ", "
        << "count = " << p.count << ", "
        << "threads = " << p.threads << ", "
        << "threadpool = " << p.threadpool << ", "
        << "generate = " << p.generateNew << "\n";
    return 0;
}

/* 
*  Note:   durationExec is longer than durationTotal in multithreading applications because
*            durationExec time occurs simultanously and is added up, where durationTotal is
*            simply start to finish.
*  @brief: prints stats about the algorithm execution post execution
*/
void printStats(params& p, results r, std::ostream& os) {
    if (r.algoDuration.count() != 0) 
        os << r.algoDuration.count() << " microseconds" << " - Time taken by the algorithm.\n";
    if (r.functDuration.count() != 0) 
        os << r.functDuration.count() << " microseconds" << " - Time taken to execute algorithm & supporting functions.\n";
    os << "Correct: " << r.correct << ", Total Files: " << p.count << "\n\n";
}