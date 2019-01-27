#pragma once
#include "LoadingSystem.h"


/**
 * Saves created monsters from the Player::monsterList vector into multiple files
 * Each files is a number (based on monster ID) and contains information to recreate
 * monsters later.
 */
void LoadingSystem::saveGeneratedMonsters() {

    for (int i = 0; i < Player::monsterList.size(); i++) {
        std::ofstream namesFile("MonsterList/" + std::to_string(Player::monsterList[i]->getId()) + ".txt",
                                std::ios::out);
        if (!namesFile) {
            exit(1);
        }
        if (Player::monsterList.empty()) {
            std::cerr << "no monsters to save" << std::endl;
            exit(1);
        }
        namesFile << Player::monsterList[i]->getUniqueId() << std::endl;
        namesFile << Player::monsterList[i]->getType() << std::endl;
        namesFile << Player::monsterList[i]->getName() << std::endl;
        namesFile << Player::monsterList[i]->getHealth() << std::endl;
        namesFile << Player::monsterList[i]->getMaxHealth() << std::endl;
        namesFile << Player::monsterList[i]->getArmor() << std::endl;
        namesFile << Player::monsterList[i]->getPower() << std::endl;
        namesFile << Player::monsterList[i]->getExperiencePoints() << std::endl;
        namesFile << Player::monsterList[i]->getMaxExperiencePoints() << std::endl;
        namesFile << Player::monsterList[i]->getLevel() << std::endl;
        namesFile << Player::monsterList[i]->getDescription() << std::endl;
    }
}
/**
 * Saves player's name and gold they collected into a single file
 */
void LoadingSystem::savePlayer() {
    std::ofstream namesFile("PlayerList/Player.txt", std::ios::out);
    if (!namesFile) {
        exit(1);
    }
    namesFile << Player::getPlayerName() << std::endl;
    namesFile << Player::getGold() << std::endl;
}

/**
 * Saves items into a single file
 * Each line is predefined amount of the item from the Items list
 * Eg. first line is amount of healing potions etc.
 */
void LoadingSystem::saveItems() {
    std::ofstream namesFile("ItemList/Items.txt", std::ios::out);
    if (!namesFile) {
        exit(1);
    }
    int healingPotion = 0;
    int firePotion = 0;
    for (int i = 0; i < Player::backpack.size(); i++) {
        if (Player::backpack[i]->getItemName() == "Healing Potion") {
            healingPotion++;
        } else if (Player::backpack[i]->getItemName() == "Fire Potion") {
            firePotion++;
        }
    }

    namesFile << healingPotion << std::endl;
    namesFile << firePotion << std::endl;
}

/**
 * Loads Monsters from files and recreates monsters into a vector back again
 * Some minor nuisance is not loading variables such as "inRoster" that determinate
 * if monster is in a team roster, but I left it as a feature.
 */
void LoadingSystem::loadGeneratedMonsters() {
    int index;                                       //used to iterate through all files in the folder
    Player::monsterList.clear();
    for (index = 1; index < 200; index++) {          //Game supports up to 200 monsters
        std::ifstream inClientFile("MonsterList/" + std::to_string(index) + ".txt", std::ios::in);
        std::string temp;                               //Inelegant solution to get an entire string for description
        int uniqueId;
        std::string name;
        std::string type;
        int health;
        int maxHealth;
        int armor;
        int power;
        int experiencePoints;
        int maxExperiencePoints;
        int level;
        std::string description;

        if (!inClientFile) {
            break;
        }

        if (inClientFile.is_open()) {
            inClientFile >> uniqueId;
            inClientFile >> type;
            inClientFile >> name;
            inClientFile >> health;
            inClientFile >> maxHealth;
            inClientFile >> armor;
            inClientFile >> power;
            inClientFile >> experiencePoints;
            inClientFile >> maxExperiencePoints;
            inClientFile >> level;
            while (std::getline(inClientFile, temp)) {
                description = temp;
            }


            if (type == "Fire") {
                Player::monsterList.push_back(Monster::createEmptyMonster(1)); //creates template monster to populate
            } else if (type == "Water") {
                Player::monsterList.push_back(Monster::createEmptyMonster(2)); //creates template monster to populate
            } else if (type == "Rock") {
                Player::monsterList.push_back(Monster::createEmptyMonster(3)); //creates template monster to populate
            } else {
                break;
            }
            Player::monsterList[Player::monsterList.size() - 1]->setId(index);
            Player::monsterList[Player::monsterList.size() - 1]->setType(type);
            Player::monsterList[Player::monsterList.size() - 1]->setName(name);
            Player::monsterList[Player::monsterList.size() - 1]->setHealth(health);
            Player::monsterList[Player::monsterList.size() - 1]->setMaxHealth(maxHealth);
            Player::monsterList[Player::monsterList.size() - 1]->setArmor(armor);
            Player::monsterList[Player::monsterList.size() - 1]->setPower(power);
            Player::monsterList[Player::monsterList.size() - 1]->setExperiencePoints(experiencePoints);
            Player::monsterList[Player::monsterList.size() - 1]->setMaxExperiencePoints(maxExperiencePoints);
            Player::monsterList[Player::monsterList.size() - 1]->setLevel(level);
            Player::monsterList[Player::monsterList.size() - 1]->setDescription(description);

            inClientFile.close();
            Monster::uniqueId = index;
        }
    }
}


/**
 * Loads items from the single file
 * Creates items back for the player to use
 * They won't be in the same order as before however.
 */
void LoadingSystem::loadItems() {
    int healingPotion;
    int firePotion;

    Player::backpack.clear();
    std::ifstream inClientFile("ItemList/Items.txt", std::ios::in);

    if (!inClientFile) {
        std::cout << "Error loading items" << std::endl;
    }

    if (inClientFile.is_open()) {
        inClientFile >> healingPotion;
        inClientFile >> firePotion;
        for (int i = 0; i < healingPotion; i++) {
            Player::backpack.push_back(Item::createItem(1));
        }
        for (int i = 0; i < firePotion; i++) {
            Player::backpack.push_back(Item::createItem(2));
        }
        inClientFile.close();
    }
}

/**
 * Loads player from the single file
 * gets gold and name and populates Player variables
 */
void LoadingSystem::loadPlayer() {
    std::ifstream inClientFile("PlayerList/Player.txt", std::ios::in);
    int gold;
    std::string playerName;
    std::string temp;
    if (!inClientFile) {
        exit(1);
    }
    if (inClientFile.is_open()) {

        std::getline(inClientFile, temp);
        playerName = temp;
        inClientFile >> gold;
        Player::setPlayerName(playerName);
        Player::setGold(gold);
        inClientFile.close();
    }
}


