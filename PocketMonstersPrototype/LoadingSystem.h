#pragma once
#include <fstream>
#include <cstdlib>
#include <string>
#include "Menu.h"

//Everything is static as I don't need more than one instance of Loading system
class LoadingSystem {
public:
    //Saving
    static void saveGeneratedMonsters();
    static void savePlayer();
    static void saveItems();
    //Loading
    static void loadGeneratedMonsters();
    static void loadPlayer();
    static void loadItems();
};


