#pragma once
#include <fstream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <random>


class RandomGenerator {
public:
    //Default Constructor
    RandomGenerator();
    //Getter
    static bool getMonsterName();                    //Returns True if loaded successfully
    static std::string getRandomMonsterName();

    static int randomValue(int minValue, int maxValue);
    static std::string createRandomDescription();

    static std::vector<std::string> monsterNames;
};

