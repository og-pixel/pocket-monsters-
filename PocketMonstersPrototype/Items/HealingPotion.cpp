#include <iostream>
#include "HealingPotion.h"
#pragma once

HealingPotion::HealingPotion() {
    itemName = "Healing Potion";
    itemDescription = "Heals your monster during combat for 10 points";
    itemPrice = 50;
    targetsAlly = true;
}

void HealingPotion::useItem(Monster& targetedMonster){
    std::cout << "Used " + itemName << std::endl;
    targetedMonster.heal(10);
}

std::string HealingPotion::getItemName(){
    return itemName;
}

void HealingPotion::printItemDescription(){
    std::cout << itemDescription << std::endl;
}

int HealingPotion::getId() {
    return id;
}

int HealingPotion::getItemPrice() {
    return itemPrice;
}

bool HealingPotion::getTargetsAlly(){
    return targetsAlly;
}
