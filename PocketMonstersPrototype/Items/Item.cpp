#include "Item.h"
#include "HealingPotion.h"
#include "FirePotion.h"
#pragma once

Item::Item(){}  //Default Constructor

void Item::useItem(Monster& targetedMonster){
}

Item *Item::createItem(int choice) {
    if (choice == 1){
        return new HealingPotion();
    }
    else if (choice == 2){
        return new FirePotion();
    }
}

std::string Item::getItemName(){
    return 0;
}

void Item::printItemDescription(){
}

int Item::getId(){
    return 0;
}

int Item::getItemPrice() {
    return 0;
}

bool Item::getTargetsAlly(){
    return 0;
}
