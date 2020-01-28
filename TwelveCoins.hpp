/**
 * @file: TwelveCoins.hpp
 * @brief: 
 * 
 * @date: 1/25/2020
 * @author: Dan Sager
 */

#ifndef TwelveCoins_HPP
#define TwelveCoins_HPP

#include <vector>

const int normalWeight = 10;
const int lighter = normalWeight -1;
const int heavier = normalWeight +1;

struct coin {
    int index;
    int weight;

    coin() {}
    coin(int i, int w) : index(i), weight(w) {}
    //~coin();

    void set(int i, int w) { index=i; weight=w; }  //setter
    int getIndex() const { return index; }  //getter
    int getWeight() const { return weight; }  //getter
};

class TwelveCoins {
public:
    void init();
    coin exec(std::vector<int> input);
    int validate(coin out, coin ans);
    std::vector<int> slice(std::vector<int> v, int m, int n);
    int weigh(int a, int b);
    int weigh(std::vector<int> a, std::vector<int> b);
    int sum(std::vector<int> arr);
    int generate(int size);
};

#endif // TwelveCoins_HPP