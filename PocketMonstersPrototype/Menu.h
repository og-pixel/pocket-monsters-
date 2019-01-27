#pragma once
#include "RandomGenerator.h"
#include "Player.h"
#include "LoadingSystem.h"
#include <fstream>
#include <windows.h>

class Menu {
public:
    //Constructor
	Menu();
    //Menu Displays
	void drawWelcomeMenu();
	void drawMenu();
	void drawArenaSettings();
	void drawLoadMenu();
    void drawDebuggingMenu();
    void drawNewGameWarning();
    void drawShopMenu();
    void drawPlayerProfile();
    void drawStarterMonsterMenu();
    void drawDifficultyMenu();
    static void clear();

private:
};