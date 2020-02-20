/**
 * @file: ExecuteCoins.cpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <algorithm>
#include <semaphore.h> //linux only
#include <unistd.h> //linux only
#include <ThreadPool.h>
#include "ExecuteCoins.hpp"
#include "TwelveCoins.hpp"

TwelveCoins twelvecoins;
results r;
//Multithread Variables
std::mutex mtx;             // prevents updating global variables simulationously
sem_t sem;                  // counting semaphore to regulate number of active threads
std::chrono::microseconds durationExec = std::chrono::milliseconds(0);
std::chrono::microseconds durationTotal = std::chrono::milliseconds(0);
int numCorrect = 0;         // tallies up number of numCorrect outputs
//Multithread Variables

/**
 * @brief: Executes the algorithm using SingleThreading. Is the most simple implementation
 *           for this specific case and should be used to analyze what is happening.
 *         First we generate an input and answers txt file in twelvecoins.generate.
 *         We then load both files into vectors so that their entire x amount of inputs
 *           can be iterated upon.
 */
results ExecuteCoins::initializeSingle(params p)
{
    if (p.generateNew) twelvecoins.generate(p.count);
    std::vector<std::vector<int>> inpVect = twelvecoins.initInput();
    std::vector<coin> ansVect = twelvecoins.initAnswers();
    int size = std::min((int)ansVect.size(),p.count);

    // Execute the algo
    int i = 0;
    auto startTotal = std::chrono::high_resolution_clock::now();
    for (std::vector<std::vector<int>>::iterator it = inpVect.begin() ; it != inpVect.end() && i < size; ++it, ++i) {
        std::vector<int> arr = *it;
        auto startAlgo = std::chrono::high_resolution_clock::now();
        coin out = twelvecoins.exec(arr);
        auto stopAlgo = std::chrono::high_resolution_clock::now();
        durationExec += std::chrono::duration_cast<std::chrono::microseconds>(stopAlgo - startAlgo);
        numCorrect += twelvecoins.validate(out,ansVect.at(i));
    }
    auto stopTotal = std::chrono::high_resolution_clock::now();
    durationTotal = std::chrono::duration_cast<std::chrono::microseconds>(stopTotal - startTotal);
    r.correct = numCorrect;
    r.algoDuration = durationExec;
    r.functDuration = durationTotal;
    return r;
}

/**
 * @brief: Because executing std::thread requires a function to execute upon, this function was
 *           made so that in initializeMulti and initializePool could call upon it.
 *         mtx used so global variables can stay consistent and not deal with race conditions.
 *         sem_post signifies that execution has concluded and another thread can be created.
 */
void execMulti(std::vector<int> arr, coin ans)
{
    auto startAlgo = std::chrono::high_resolution_clock::now();
    coin out = twelvecoins.exec(arr);
    auto stopAlgo = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopAlgo - startAlgo);
    bool correct = twelvecoins.validate(out,ans);

    mtx.lock();
    durationExec += duration;
    numCorrect += correct;
    sem_post(&sem);
    mtx.unlock();

    return;
}

/**
 * @brief: Executes the algorithm using a vector to store new threads which are larger 
 *           joined to make sure no thread is left open and all inputs are accounted for.
 *         Uses a semaphore for thread count regulation. sem_wait slowly decremented until
 *         it reaches 0, at which point, no new threads will be deployed.
 */
results ExecuteCoins::initializeMulti(params p)
{
    sem_init(&sem,0,p.threads);

    if (p.generateNew) twelvecoins.generate(p.count);
    std::vector<std::vector<int>> inpVect = twelvecoins.initInput();
    std::vector<coin> ansVect = twelvecoins.initAnswers();
    int size = std::min((int)ansVect.size(),p.count);

    // Execute the algo
    auto startTotal = std::chrono::high_resolution_clock::now();

    /* Using a normal system of pushing_back every thread created a problem
    *  when the thread count exceed 32,737. As a result, this method was adapted
    *  where the thread vector has a max, once it hit, it will join all threads
    *  and then repeat. Avoiding the vector becoming too large. */ 
    int count = 0;
    while (count < size) {
        std::vector<std::thread> threads(std::min(10000,(size-count)));
        for (size_t i = 0; i < threads.size(); ++i) {
            sem_wait(&sem); // Limits the active number of threads to equal p.threads
            std::vector<int> arr = inpVect.at(count+i); // .at() is O(1) time complexity
            coin ans = ansVect.at(count+i);
            threads[i] = std::thread(execMulti,arr,ans);
        }
        for (size_t i = 0; i < threads.size(); ++i) {
            threads[i].join();
            count++;
        }
    }

    auto stopTotal = std::chrono::high_resolution_clock::now();
    durationTotal = std::chrono::duration_cast<std::chrono::microseconds>(stopTotal - startTotal);
    sem_destroy(&sem);
    r.correct = numCorrect;
    r.algoDuration = durationExec;
    r.functDuration = durationTotal;
    return r;
}

/**
 * @brief: Executes the algorithm using a threadpool in contrast to initalizeMulti, this will 
 *           reuse threads instead of creating and deleting a thread when necessary.
 *         ThreadPool is implemented from https://github.com/mtrebi/thread-pool.
 *         Uses a semaphore for thread count regulation. Used more in initalizeMulti.
 */
results ExecuteCoins::initializePool(params p)
{
    ThreadPool pool(p.threads); // Create pool with specified thread count
    pool.init(); // Initialize pool

    sem_init(&sem,0,p.threads);

    if (p.generateNew) twelvecoins.generate(p.count);
    std::vector<std::vector<int>> inpVect = twelvecoins.initInput();
    std::vector<coin> ansVect = twelvecoins.initAnswers();
    int size = std::min((int)ansVect.size(),p.count);

    // Execute the algo
    int i = 0;
    auto startTotal = std::chrono::high_resolution_clock::now();

    for (std::vector<std::vector<int>>::iterator it = inpVect.begin() ; it != inpVect.end() && i < size; ++it, ++i) {
        sem_wait(&sem);
        std::vector<int> arr = *it;
        coin ans = ansVect.at(i);

        pool.submit(execMulti, arr, ans);           
    }

    usleep(10); // Prevents pool.shutdown() from hanging
    pool.shutdown();

    auto stopTotal = std::chrono::high_resolution_clock::now();
    durationTotal = std::chrono::duration_cast<std::chrono::microseconds>(stopTotal - startTotal);
    sem_destroy(&sem);
    r.correct = numCorrect;
    r.algoDuration = durationExec;
    r.functDuration = durationTotal;
    return r;
}