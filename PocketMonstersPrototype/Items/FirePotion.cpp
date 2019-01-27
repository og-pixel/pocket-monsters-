#include <iostream>
#include "FirePotion.h"
#pragma once

FirePotion::FirePotion() {
    itemName = "Fire Potion";
    itemDescription = "A liquid fire in the glass bottle\n"
            "Throw at the enemy to deal 15 Damage\n"
            "Ignores Armor";
    itemPrice = 80;
    targetsAlly = false;
}

void FirePotion::useItem(Monster& targetedMonster){
    std::cout << "Used " + itemName << std::endl;
    targetedMonster.setHealth(targetedMonster.getHealth() - 15);
    if(targetedMonster.getHealth() < 0)targetedMonster.setHealth(0);
}

std::string FirePotion::getItemName(){
    return itemName;
}

void FirePotion::printItemDescription(){
    std::cout << itemDescription << std::endl;
}

int FirePotion::getId(){
    return id;
}

int FirePotion::getItemPrice() {
    return itemPrice;
}

bool FirePotion::getTargetsAlly(){
    return targetsAlly;
}
