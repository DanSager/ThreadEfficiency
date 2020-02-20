/**
 * @file: ThreadEfficiency.hpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#ifndef ThreadEfficiency_HPP
#define ThreadEfficiency_HPP

#include "Params.hpp"

int readCommandParams(params& p, int argc, char *argv[]);
void printParamSettings();
int printParams(params& p, std::ostream& os);
void printStats(params& p, results r, std::ostream& os);

#endif // ThreadEfficiency_HPP