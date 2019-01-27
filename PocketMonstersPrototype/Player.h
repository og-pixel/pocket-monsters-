#include <iostream>
#include <vector>
#include "Items/Item.h"
#include "Monster/Monster.h"
#pragma once

class Player {
public:
	//Constructor
	Player();
	//Static lists for player
	static std::vector<Monster*> monsterList;
	static std::vector<Item*> backpack;
	//Menu Displays
	static void displayBackpackContent();
	static int displayBackpackContentForArena();
	static void displayMonsterListContent();
	//Getters
    static int getGold();
    static std::string getPlayerName();
	static int getRosterSize();
	//Setters
    static void setPlayerName(std::string playerName);
    static void setGold(int gold);
private:
    static std::string playerName;
    static int gold;
};




