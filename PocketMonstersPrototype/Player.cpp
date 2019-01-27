#include "Player.h"
#include "Menu.h"
#pragma once

std::vector<Monster *> Player::monsterList;
std::vector<Item *> Player::backpack;
int Player::gold;
std::string Player::playerName;

Player::Player(){}

//Setters
void Player::setPlayerName(std::string playerName) {
    Player::playerName = playerName;}
void Player::setGold(int gold) {
    Player::gold = gold;}
//Getters
int Player::getGold() {
    return gold;}
std::string Player::getPlayerName() {
    return playerName;}
int Player::getRosterSize() {
    int rosterSize = 0;
    for (int i = 0; i < monsterList.size(); i++) {
        if (monsterList[i]->isInRoster()) {
            rosterSize++;
        }
    }
    return rosterSize;
}


/**
 * Displays backpack content that user can browse
 * It only shows 10 elements per page
 */
void Player::displayBackpackContent() {
    int page = 1;                               //each page equals 10 elements from the backpack
    std::string pageChoice = "0";               //user interacts which page they want to see
    int backpackPages = backpack.size() / 10;   //for how many pages we need
    int backpackModulo = backpack.size() % 10;  //for the last page, as it might be non equal 10
    int itemChoice;
    while (pageChoice != "b") {
        Menu::clear();
        //If a page isn't full, we use modulo
        if (page > backpackPages) {
            for (int i = page * 10 - 10; i < page * 10 - 10 + backpackModulo; i++) {
                std::cout << i + 1 << ") " << backpack[i]->getItemName() << "\n";
            }
            //Otherwise, print all 10 elements
        } else {
            for (int i = page * 10 - 10; i < page * 10; i++) {
                std::cout << i + 1 << ") " << backpack[i]->getItemName() << "\n";
            }
        }
        //Draw Menu options
        std::cout << "************************\n"
                "Next Page = \"n\" "
                "| Previous Page = \"p\" \n" <<
                  "Choose item = " << page * 10 - 10 + 1  << "-" << page * 10  <<
                  " | Back = \"b\"" << std::endl;
        std::cin >> pageChoice;
        if (pageChoice == "n" && page < backpackPages) {        //if we want to go next page, AND
            page++;                                             //there is next page!
        } else if (pageChoice == "n" && page == backpackPages && backpackModulo > 0) {
            page++;
        }

        if (pageChoice == "p" && page > 1) {                    //if we want to go previous page, AND
            page--;                                             //there is previous page!
        }

        //This tries to change string into number, if it can, it means I chose a number
        itemChoice = atoi(pageChoice.c_str());
        if (itemChoice > page * 10 - 10 && itemChoice <= page * 10 &&
            itemChoice <= backpack.size()) {
            while (pageChoice != "b") {
                Menu::clear();
                backpack[itemChoice - 1]->printItemDescription();
                std::cout << "************************\n" <<
                          "Back = \"b\"" << std::endl;
                std::cin >> pageChoice;
            }
            pageChoice = "";//otherwise it "remembers" back and will exit the loop
        }
    }
}

/**
 * Displays backpack content that user can browse
 * It only shows 10 elements per page
 * Method is almost the same as the displayBackpackContent
 * but it has an ability to "use" item which will return its position in the array
 * to use in arena.
 */
int Player::displayBackpackContentForArena() {
    int page = 1;                               //each page equals 10 elements from the backpack
    std::string pageChoice = "0";               //user interacts which page they want to see
    int backpackPages = backpack.size() / 10;   //for how many pages we need
    int backpackModulo = backpack.size() % 10;  //for the last page, as it might be non equal 10
    int itemChoice;
    while (pageChoice != "b") {
        Menu::clear();
        //If a page isn't full, we use modulo
        if (page > backpackPages) {
            for (int i = page * 10 - 10; i < page * 10 - 10 + backpackModulo; i++) {
                std::cout << i + 1 << ") " << backpack[i]->getItemName() << "\n";
            }
            //Otherwise, print all 10 elements
        } else {
            for (int i = page * 10 - 10; i < page * 10; i++) {
                std::cout << i + 1 << ") " << backpack[i]->getItemName() << "\n";
            }
        }
        //Draw Menu options
        std::cout << "************************\n"
                "Next Page = \"n\" "
                "| Previous Page = \"p\" \n" <<
                  "Choose item = " << page * 10 - 10 + 1 << "-" << page * 10 <<
                  " | Back = \"b\"" << std::endl;
        std::cin >> pageChoice;
        if (pageChoice == "n" && page < backpackPages) {        //if we want to go next page, AND
            page++;                                             //there is next page!
        } else if (pageChoice == "n" && page == backpackPages && backpackModulo > 0) {
            page++;
        }

        if (pageChoice == "p" && page > 1) {                    //if we want to go previous page, AND
            page--;                                             //there is previous page!
        }

        //This tries to change string into number, if it can, it means I chose a number
        itemChoice = atoi(pageChoice.c_str());
        if (itemChoice > page * 10 - 10 && itemChoice <= page * 10 && itemChoice <= backpack.size()) {
            while (pageChoice != "b") {
                Menu::clear();
                backpack[itemChoice - 1]->printItemDescription();
                std::cout << "************************\n"
                        "Use Item = \"u\" | Back = \"b\"" << std::endl;
                std::cin >> pageChoice;

                if (pageChoice == "u") {
                    return itemChoice - 1;  //if i choose to use the item, i return its position
                }

            }
            pageChoice = "";    //otherwise it "remembers" back and will exit the loop
        }
        Menu::clear();
    }
    return -1;
}

/**
 * Displays monster content that user can browse
 * It only shows 10 elements per page
 * User can heal monsters and get their details statistics
 * and add them to the team roster for arena.
 */
void Player::displayMonsterListContent() {
    int page = 1;                                      //each page equals 10 elements from the backpack
    std::string pageChoice = "0";                     //user interacts which page they want to see
    int monsterListPages = monsterList.size() / 10;   //for how many pages we need
    int monsterListModulo = monsterList.size() % 10;  //for the last page, as it might be non equal 10
    int monsterChoice;

    while (pageChoice != "b") {
        Menu::clear();
        //If a page isn't full, we use modulo
        if (page > monsterListPages) {
            for (int i = page * 10 - 10; i < page * 10 - 10 + monsterListModulo; i++) {
                std::cout << monsterList[i]->getId() << ") " << monsterList[i]->getName()
                          << " " << monsterList[i]->getType() << " Lvl: " << monsterList[i]->getLevel()
                          << " In roster: " << monsterList[i]->isInRoster() << std::endl;
            }
            //Otherwise, print all 10 elements
        } else {
            for (int i = page * 10 - 10; i < page * 10; i++) {
                std::cout << monsterList[i]->getId() << ") " << monsterList[i]->getName()
                          << " " << monsterList[i]->getType() << " Lvl: " << monsterList[i]->getLevel() << "\n"
                          << "In roster: " << monsterList[i]->isInRoster() << std::endl;
            }
        }

        //Draw Menu options
        std::cout << "************************\n"
                "Next Page = \"n\" "
                "| Previous Page = \"p\" \n" <<
                  "Choose item = " << page * 10 - 10 + 1 << "-" << page * 10 <<
                  " | Back = \"b\"" << std::endl;
        std::cin >> pageChoice;
        if (pageChoice == "n" && page < monsterListPages) {        //if we want to go next page, AND
            page++;                                                 //there is next page!
        } else if (pageChoice == "n" && page == monsterListPages && monsterListModulo > 0) {
            page++;
        }

        if (pageChoice == "p" && page > 1) {                    //if we want to go previous page, AND
            page--;                                             //there is previous page!
        }

        //This tries to change string into number, if it can, it means I chose a number
        monsterChoice = atoi(pageChoice.c_str());
        // if (monsterChoice fits within page range) AND monsterChoice is less or equal to monsterList size
        // Second part is to prevent modulo error, eg if list has less than 10 elements, size will be smaller
        if ((monsterChoice > page * 10 - 10 && monsterChoice <= page * 10) &&
            monsterChoice <= monsterList.size()) {
            while (pageChoice != "b") {
                Menu::clear();
                int healthDifference;   //for healing purporses
                monsterList[monsterChoice - 1]->getDetails();
                healthDifference = monsterList[monsterChoice - 1]->getMaxHealth();
                healthDifference = healthDifference - monsterList[monsterChoice - 1]->getHealth();
                std::cout << "************************\n" <<
                          "Back = \"b\" | Full Heal (" << healthDifference << " gold) = \"h\"\n" <<
                          "Add to team roster = \"a\"" << std::endl;
                std::cin >> pageChoice;

                //Can heal if I have enough gold and there is actually something to heal
                if (pageChoice == "h" && healthDifference > 0 && healthDifference < Player::getGold()) {
                    monsterList[monsterChoice - 1]->heal(healthDifference);
                    Player::setGold(Player::getGold() - healthDifference);
                }

                //If we want to add or remove a monster from the roster
                if (pageChoice == "a" && !monsterList[monsterChoice - 1]->isInRoster()) {
                    monsterList[monsterChoice - 1]->setInRoster(true);
                } else if (pageChoice == "a" && monsterList[monsterChoice - 1]->isInRoster()) {
                    monsterList[monsterChoice - 1]->setInRoster(false);
                }
            }
            pageChoice = "";//otherwise it "remembers" back and will exit the loop
        }
    }
}



