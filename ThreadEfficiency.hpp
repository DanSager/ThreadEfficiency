/**
 * @file: ThreadEfficiency.hpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#ifndef ThreadEfficiency_HPP
#define ThreadEfficiency_HPP

enum algo {none, balls, floors};

struct params {
    algo algoName = none;
    int threads = 1;
    bool threadpool = false;
    bool validate = true;
};

int readCommandParams(int argc, char *argv[]);
void printParamSettings();
int printParams();

#endif // ThreadEfficiency_HPP