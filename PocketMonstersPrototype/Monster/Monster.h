#pragma once
#include <string>
#include <iostream>


class Monster {
public:
    static int uniqueId; //static because ID should be an unqiue way to find a monster, like in pokemon, It might need to be an array instead

    //Default Constructor
    Monster ();
    //Factories
    static Monster *createMonster(int choice); //Factory Method
    static Monster *createOpponentMonster(int choice); //Alternative Factory Method for Opponent Monsters
    static Monster *createEmptyMonster(int choice); //Alternative Factory Method for loading system
    //Monster Fighting Abilities
    virtual void getDetails();
    virtual void specialAttack(Monster& defendingMonster) = 0;
    virtual void basicAttack(Monster& secondMonster);
    virtual void block(int amount);
    virtual void heal(int amountToHeal);
    virtual void evolve();
    //STATIC GETTER
    static int getUniqueId();
    //GETTERS
    virtual std::string getName() = 0;
    virtual int getHealth() = 0;
    virtual int getMaxHealth() = 0;
    virtual int getPower() = 0;
    virtual bool getFainted() = 0;
    virtual int getExperiencePoints() = 0;
    virtual int getLevel() = 0 ;
    virtual int getArmor()= 0;
    virtual int getMaxExperiencePoints() = 0;
    virtual int getId() = 0;
    virtual std::string getType() = 0;
    virtual std::string getDescription() = 0;
    virtual std::string getWeakness() = 0;
    // SETTERS
    virtual void setName(std::string name) = 0;
    virtual void setMaxHealth(int maxHealth);
    virtual void setArmor(int armor);
    virtual void setPower(int power);
    virtual void setExperiencePoints(int experiencePoints) = 0;
    virtual void setMaxExperiencePoints(int maxExperiencePoints) = 0;
    virtual void setLevel(int level);
    virtual void setId(int id);
    virtual void setHealth(int setHealthVariable);
    virtual void setType(const std::string &type);
    virtual void setDescription(const std::string &description) = 0;
    virtual void setFainted(bool fainted) = 0;
    virtual bool isInRoster();
    virtual void setInRoster(bool inRoster);

};
