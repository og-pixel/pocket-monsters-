#pragma once
#include "Menu.h"
#include "Arena.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Used to colour terminal, used sparingly as its a bit problematic
int difficulty = 1;
int monsterLevelDifficulty = 1;

Menu::Menu() {}

/**
 * Draws First Welcome menu
 * Either starts the game from scratch
 * or loads previous game
 */
void Menu::drawWelcomeMenu() {
    SetConsoleTextAttribute(hConsole, 11);
    int choice;
    std::cout << "*******************************\n" <<
              "Welcome to POCKET MONSTERS!\n" <<
              "1) START NEW GAME\n" <<
              "2) LOAD\n" <<
              "0) EXIT\n" << std::endl;
    std::cin >> choice;
    if (choice == 1) {
        clear();
        std::ifstream previousSave("MonsterList/1.txt");
        if (previousSave) {
            previousSave.close();
            drawNewGameWarning();
        }
        std::string name;
        while (name.length() == 0) {
            std::cout << "Please Choose a name!" << std::endl;
            std::getline(std::cin, name);// >> name;
        }
        Player::setPlayerName(name);
        drawStarterMonsterMenu();
        drawMenu();
    } else if (choice == 2) {
        clear();
        std::ifstream previousSave("MonsterList/1.txt");
        if (!previousSave) {
            std::cout << "Nothing to load!" << std::endl;
            previousSave.close();
            drawWelcomeMenu();
        } else {
            LoadingSystem::loadGeneratedMonsters();
            LoadingSystem::loadItems();
            LoadingSystem::loadPlayer();
            drawMenu();
        }
    } else if (choice == 0) {
        clear();
        exit(0);
    }
    else{
        clear();
        drawWelcomeMenu();
    }
}

/**
 * Draws Main Menu
 * From here user can start their journey
 * (also little debug menu for developer)
 */
void Menu::drawMenu() {
    SetConsoleTextAttribute(hConsole, 12);
    int choice;
    std::cout << "*******************************\n" <<
              "Welcome to POCKET MONSTERS!\n" <<
              "1) Enter Arena\n" <<
              "2) Player Profile\n" <<
              "3) Save/Load\n" <<
              "4) Shop\n" <<
              "5) Debug (for developer)\n" <<
              "0) Exit\n";
    std::cin >> choice;
    if (choice == 1) {
        clear();
        drawArenaSettings();
    } else if (choice == 2) {
        clear();
        drawPlayerProfile();
    } else if (choice == 3) {
        clear();
        drawLoadMenu();
    } else if (choice == 4) {
        clear();
        drawShopMenu();
    } else if (choice == 5) {
        clear();
        drawDebuggingMenu();
    }
    else if(choice == 0){
        exit(0);
    }
    else{
        clear();
        drawMenu();
    }

}

/**
 * Draws Settings for Arena
 * User can change difficulty (1 for random, 2 for slightly smarter)
 * Also choose level of enemy monsters (from 1 to 3)
 * User can also choose a team for all monsters they have (minimum 1, max 3)
 */
void Menu::drawArenaSettings() {
    SetConsoleTextAttribute(hConsole, 15);
    int choice = 0;
    std::cout << "*******************************\n" <<
              "Welcome to the Arena!\n" <<
              "You can choose your team roster here\n" <<
              "Remember that you are allowed to use items\n" <<
              "You win battle by decreasing opponent's monsters life to zero\n" <<
              "1) ENTER ARENA\n" <<
              "2) Prepare Team\n" <<
              "3) Choose Difficulty\n" <<
              "0) Back\n\n";
    std::cin >> choice;
    if (choice == 0) {
        clear();
        drawMenu();
    } else if (choice == 1) {
        std::cout << "ENTER THE ARENA" << std::endl;
        if (Player::getRosterSize() > 3) {
            clear();
            std::cout << "Your team is too big\n";
            drawArenaSettings();
        } else if (Player::getRosterSize() <= 0) {
            clear();
            std::cout << "Your don't have monsters in roster\n";
            drawArenaSettings();
        } else {
            Arena *arena = new Arena(Player::getRosterSize(), difficulty, monsterLevelDifficulty);
            clear();
            arena->drawArena();
            drawMenu();
        }
    } else if (choice == 2) {
        std::cout << "PREPARE TEAM" << std::endl;
        Player::displayMonsterListContent();
        clear();
        drawArenaSettings();
    } else if (choice == 3) {
        drawDifficultyMenu();
    } else if (choice == 0) {
        clear();
        drawMenu();
    }
    else {
        clear();
        drawArenaSettings();
    }
}

/**
 * Draws loading menu where user can save or load their progress
 * (items, monsters, gold and names)
 */
void Menu::drawLoadMenu() {
    int choice = 0;
    std::cout << "*******************************\n" <<
              "Save or Load Your Progress!\n" <<
              "1) Save\n" <<
              "2) Load Last Progress\n" <<
              "0) Back\n";
    std::cin >> choice;
    if (choice == 1) {
        LoadingSystem::saveGeneratedMonsters();
        LoadingSystem::saveItems();
        LoadingSystem::savePlayer();
        clear();
        drawMenu();
    } else if (choice == 2) {
        std::ifstream previousSave("MonsterList/1.txt");
        if (!previousSave) {
            previousSave.close();
            clear();
            std::cout << "Nothing to load!" << std::endl;
            drawMenu();
        } else {
            LoadingSystem::loadGeneratedMonsters();
            LoadingSystem::loadItems();
            LoadingSystem::loadPlayer();
            clear();
            std::cout << "Load Successful!" << std::endl;
            drawMenu();
        }
    } else if (choice == 0) {
        clear();
        drawMenu();
    } else {
        clear();
        drawLoadMenu();
    }
}

/**
 * Draws debugging menu for developer to display
 * some variables
 */
void Menu::drawDebuggingMenu() {
    int choice = 0;
    std::cout << "*******************************\n" <<
              "DEBUGGING MENU!\n" <<
              "1) Random Generator\n" <<
              "2) Get Monster Unique ID \n" <<
              "3) Create Random Monster \n" << std::endl;
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "enter two values" << std::endl;
        int firstValue, secondValue;
        std::cin >> firstValue >> secondValue;
        std::cout << "A random Value between " << firstValue << " and " << secondValue << "\n" <<
                  RandomGenerator::randomValue(firstValue, secondValue);
    } else if (choice == 2) {
        std::cout << "Unique ID: " << Monster::getUniqueId() << std::endl;
    } else if (choice == 3) {
        Player::monsterList.push_back(Monster::createMonster(RandomGenerator::randomValue(1, 2)));
    }
    drawMenu();
}

/**
 * Draws a warning when a user wants to start a new game
 * Game only supports one save and will remove all previous files
 */
void Menu::drawNewGameWarning() {
    SetConsoleTextAttribute(hConsole, 10);
    int choice = 0;
    std::cout << "*******************************\n" <<
              "WARNING\n" <<
              "Game currently only supports only one save file!\n" <<
              "Creating a new game will override the last one \n" <<
              "Are you sure you wish to continue?\n" <<
              "1) Yes, delete previous game\n" <<
              "2) No, go back\n" << std::endl;
    std::cin >> choice;
    if (choice == 1) {
        clear();
        std::string monsterSave;
        system("del MonsterList\\*.txt"); // DOS
        system("del ItemList\\*.txt"); // DOS
        system("del PlayerList\\*.txt"); // DOS
    } else if (choice == 2) {
        clear();
        drawWelcomeMenu();
    }
    else{
        clear();
        drawNewGameWarning();
    }
}

/**
 * Draws shop menu where user can buy items
 * Shopkeeper has its own vector of items, however, its infinite to buy
 */
void Menu::drawShopMenu() {
    SetConsoleTextAttribute(hConsole, 15);
    int choice = 0;
    int itemChoice = 0;
    std::cout << "*******************************\n" <<
              "Welcome to the Shop!\n" <<
              "We sell items and potions to improve your\n" <<
              "chances in combat.\n" <<
              "1) Buy Some Items\n" <<
              "0) Back\n\n" << std::endl;
    std::cin >> choice;
    if (choice == 1) {
        clear();
        std::vector<Item *> shopKeeper; //shopkeep has its own vector of items
        //It creates items in the backpack, only issue is that all of those items have to be in order to create
        //correctly, so if I create another item, it has to go under "createItem(3)"
        shopKeeper.push_back(Item::createItem(1));
        shopKeeper.push_back(Item::createItem(2));
        itemChoice = -1;
        while (itemChoice != 0) {
            std::cout << "You have " << Player::getGold() << " gold" << std::endl;
            std::cout << "What would you like to buy?\n" << std::endl;
            for (int i = 0; i < shopKeeper.size(); i++) {
                std::cout << i + 1 << ") " << shopKeeper[i]->getItemName() << " " << shopKeeper[i]->getItemPrice()
                          << " gold" << std::endl;
            }
            std::cout << "0) Back" << std::endl;

            std::cin >> itemChoice;
                //If we choose item within range AND we can afford that item
            clear();
            if (shopKeeper.size() >= itemChoice -1  && shopKeeper[itemChoice - 1]->getItemPrice() <= Player::getGold()) {
                Player::setGold(Player::getGold() - shopKeeper[itemChoice - 1]->getItemPrice());
                Player::backpack.push_back(Item::createItem(itemChoice));
                std::cout << "You have bought: " << shopKeeper[itemChoice - 1]->getItemName() << std::endl;
            }
        }
    } else if (choice == 0) {
        clear();
        drawMenu();
    } else {
        clear();
        drawShopMenu();
    }
    clear();
    drawMenu();
}

/**
 * Draws menu for user to choose their difficulty in
 * arena
 */
void Menu::drawDifficultyMenu() {
    clear();
    int choice = 0;
    std::cout << "*******************************\n" <<
              "Choose Difficulty\n" <<
              "You can Choose From\n"
              "1) AI Difficulty: " << difficulty << "\n" <<
              "2) Enemy Monster Level: " << monsterLevelDifficulty << "\n" <<
              "0) Back\n\n";
    std::cin >> choice;
    if (choice == 1) {
        if (difficulty == 1) {
            difficulty = 2;
        } else {
            difficulty = 1;
        }
        drawDifficultyMenu();
    } else if (choice == 2) {
        if (monsterLevelDifficulty == 1) {
            monsterLevelDifficulty = 2;
        } else if (monsterLevelDifficulty == 2) {
            monsterLevelDifficulty = 3;
        } else {
            monsterLevelDifficulty = 1;
        }
        drawDifficultyMenu();
    } else if (choice == 0) {
        clear();
        drawArenaSettings();
    } else {
        drawDifficultyMenu();
    }
}

/**
 * Draws Player's profile where user can
 * see their inventory, all monsters and
 * get short description of monster's special
 * abilities.
 */
void Menu::drawPlayerProfile() {
    SetConsoleTextAttribute(hConsole, 10);
    int choice = 0;
    std::cout << "*******************************\n" <<
              "Profile\n" <<
              "Name: " << Player::getPlayerName() << "\n" <<
              "Gold: " << Player::getGold() << "\n" <<
              "1) Display Backpack\n" <<
              "2) Display Monster List\n" <<
              "3) Display Monster Special Attacks Description\n" <<
              "0) Back\n\n";
    std::cin >> choice;
    if (choice == 1) {
        Player::displayBackpackContent();
        clear();
        drawPlayerProfile();
    } else if (choice == 2) {
        Player::displayMonsterListContent();
        clear();
        drawPlayerProfile();
    } else if (choice == 3) {
        SetConsoleTextAttribute(hConsole, 5);
        Menu::clear();
        std::cout << "Fire - Special has a 1.5 power multiplier.\n"
                "       Ignores armor and if weakness is found, it deals twice the damage instead.\n"
                "Water - Special has a 0.5 power multiplier.\n"
                "       Heals itself for 25% of maximum health and if weakness is found, it deals 1.4 the damage instead.\n"
                "Rock - Special has a 2 power multiplier.\n"
                "       If weakness is found, it deals triple the damage instead.\n"
                "       Self harm itself for half of basic power. (It can kill itself!)\n" << std::endl;
        drawPlayerProfile();
    } else if (choice == 0) {
        clear();
        drawMenu();
    } else {
        clear();
        drawPlayerProfile();
    }
}

/**
 * Create a starter package for the player,
 * Items, gold and one monster of the player's choice
 */
void Menu::drawStarterMonsterMenu() {
    int choice = 0;
    while (choice != 1 && choice != 2 && choice != 3) {
        clear();
        std::cout << "You will get some gold, items and a \n"
                "starter monster to get you going!\n" << std::endl;

        std::cout << "What Type of Monster would you like?\n"
                "1)Fire - Deals a lot of damage, low health\n"
                "2)Water - Deals mediocre damage, medium health, health regeneration on special attack\n"
                "3)Rock - Low damage, high health and armor, better health regeneration\n" << std::endl;
        std::cin >> choice;
        if (choice == 1 || choice == 2 || choice == 3) {
            Player::monsterList.push_back(Monster::createMonster(choice));
        }
    }
    Player::backpack.push_back(Item::createItem(1));
    Player::backpack.push_back(Item::createItem(1));
    Player::backpack.push_back(Item::createItem(2));
    Player::setGold(100);
    clear();
}

/**
 * "clear" method that creates a bunch of new lines
 */
void Menu::clear() {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}