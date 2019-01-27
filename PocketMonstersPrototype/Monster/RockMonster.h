#pragma once
#include "Monster.h"
#include <vector>
#include <iostream>


class RockMonster: public Monster {
public:
    RockMonster(int id, std::string type, std::string name, int health, int armor, int power, int level);

    void specialAttack(Monster& defendingMonster);
    void heal(int amountToHeal);
    //GETTERS
    std::string getName();
    int getId();
    int getHealth();
    int getMaxHealth();
    int getPower();
    bool getFainted();
    int getExperiencePoints();
    int getLevel();
    int getArmor();
    std::string getType();
    int getMaxExperiencePoints();
    std::string getDescription();
    bool isInRoster();
    std::string getWeakness();
    //Setters
    void setName(std::string name);
    void setId(int id);
    void setMaxHealth(int maxHealth);
    void setArmor(int armor);
    void setPower(int power);
    void setExperiencePoints(int experiencePoints);
    void setLevel(int level);
    void setMaxExperiencePoints(int maxExperiencePoints);
    void setType(const std::string &type);
    void setDescription(const std::string &description);
    void setInRoster(bool inRoster);
    void setFainted(bool fainted);
    void setHealth(int setHealthVariable);
private:
    bool fainted;
    bool inRoster;
    int experiencePoints;
    int level;
    int maxExperiencePoints;
    int id;
    int health;
    int maxHealth;
    int armor;
    int power;
    std::string description;
    std::string weakness;
    std::string type;
    std::string name;
};


