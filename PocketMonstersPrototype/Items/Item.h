#include <string>
#include "../Monster/Monster.h"
#pragma once

class Item {
public:
    //Default Constructor
    Item ();
    //Factories
    static Item *createItem(int choice);
    //Item Usage Method
    virtual void useItem(Monster& targetedMonster) = 0;
    //Menu Displays
    virtual void printItemDescription() = 0;
    //GETTERS
    virtual std::string getItemName() = 0;
    virtual bool getTargetsAlly() = 0;
    virtual int getItemPrice();
    virtual int getId();
};


