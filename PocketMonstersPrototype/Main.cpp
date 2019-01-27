#include "Main.h"
#pragma once


void main() {
    srand(time(NULL)); // Random seed for all random needs
    Menu menuTest;

    //Basic loading test if it fails, you can' get it
    if (RandomGenerator::getMonsterName()) {
        menuTest.drawWelcomeMenu();

    } else{
        std::cout << "Loading Error" << std::endl;
        std::cin.get();
        exit(1);
    }


}

