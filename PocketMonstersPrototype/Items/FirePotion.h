#include "Item.h"
#include <string>
#pragma once

class FirePotion: public Item {
public:
    //Default Constructor
    FirePotion();
    //Item Usage Method
    void useItem(Monster& targetedMonster);
    //Menu Displays
    void printItemDescription();
    //GETTERS
    std::string getItemName();
    bool getTargetsAlly();
    int getItemPrice();
    int getId();
private:
    int id;
    int itemPrice;
    bool targetsAlly;
    std::string itemName;
    std::string itemDescription;
};

