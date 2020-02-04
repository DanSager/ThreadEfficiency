/**
 * @file: Execute.cpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <semaphore.h> //linux only
#include <unistd.h> //linux only
#include "Execute.hpp"
#include "TwelveCoins.hpp"

std::mutex mtx;
sem_t sem;
TwelveCoins twelvecoins;
int correct = 0;
int totalLines = 0;

std::vector<std::thread> myThread;

void Execute::initalizeSingle(params p)
{
    if (p.algoName == coins) {
        //TwelveCoins coins;
        twelvecoins.generate(p.buildCount);
        std::vector<std::vector<int>> inpVect = twelvecoins.initInput();
        std::vector<coin> ansVect = twelvecoins.initAnswers();
        //coins.runExec(inpVect,ansVect);


        // Execute the algo
        int i = 0;
        std::chrono::microseconds duration = std::chrono::milliseconds(0);
        auto startTotal = std::chrono::high_resolution_clock::now();
        for (std::vector<std::vector<int>>::iterator it = inpVect.begin() ; it != inpVect.end(); ++it, ++i) {
            std::vector<int> arr = *it;
            auto start = std::chrono::high_resolution_clock::now();
            coin out = twelvecoins.exec(arr);
            auto stop = std::chrono::high_resolution_clock::now();
            duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            correct += twelvecoins.validate(out,ansVect.at(i));
            totalLines++;
        }
        auto stopTotal = std::chrono::high_resolution_clock::now();
        auto durationTotal = std::chrono::duration_cast<std::chrono::microseconds>(stopTotal - startTotal);
        std::cout << "Time taken by exec: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Time taken by total: " << durationTotal.count() << " microseconds" << std::endl;
        std::cout << "Correct: " << correct << ", Total: " << totalLines << std::endl;
    }
    else 
        std::cout << "this hasn't been coded yet\n\n";
}

//void Execute::execMulti(std::vector<int> arr, coin ans, int &correct, int &totalLines)
void execMulti(std::vector<int> arr, coin ans, int i)
{
    //auto start = std::chrono::high_resolution_clock::now();
    coin out = twelvecoins.exec(arr);
    //auto stop = std::chrono::high_resolution_clock::now();
    //duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    int inc = twelvecoins.validate(out,ans);
    mtx.lock();
    correct += inc;
    totalLines++;
    mtx.unlock();
    sem_post(&sem);
}

void Execute::initalizeMulti(params p)
{
    // Multithread stuff
    std::cout << "Multithread stuff" << std::endl;
    sem_init(&sem,0,p.threads);

    // Algo stuff
    if (p.algoName == coins) {
        twelvecoins.generate(p.buildCount);
        std::vector<std::vector<int>> inpVect = twelvecoins.initInput();
        std::vector<coin> ansVect = twelvecoins.initAnswers();

        // Execute the algo
        int i = 0;
        std::chrono::microseconds duration = std::chrono::milliseconds(0);
        auto startTotal = std::chrono::high_resolution_clock::now();

        for (std::vector<std::vector<int>>::iterator it = inpVect.begin() ; it != inpVect.end(); ++it, ++i) {
            sem_wait(&sem);
            std::vector<int> arr = *it;
            coin ans = ansVect.at(i);

            myThread.push_back(std::thread(execMulti,arr,ans,i));            
        }

        for (int j=0;j<myThread.size();j++)
        {
            myThread.at(j).join();
        }

        auto stopTotal = std::chrono::high_resolution_clock::now();
        auto durationTotal = std::chrono::duration_cast<std::chrono::microseconds>(stopTotal - startTotal);
        //std::cout << "Time taken by exec: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Time taken by total: " << durationTotal.count() << " microseconds" << std::endl;
        std::cout << "Correct: " << correct << ", Tota: " << totalLines << std::endl;
    }
    else 
        std::cout << "this hasn't been coded yet\n\n";

    // Multithread stuff
    sem_destroy(&sem);
}