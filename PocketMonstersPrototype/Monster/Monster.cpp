#pragma once
#include "Monster.h"
#include "FireMonster.h"
#include "WaterMonster.h"
#include "RockMonster.h"
#include "../Menu.h"

int Monster::uniqueId = 0;

Monster::Monster(){}

/**
 * Displays monster's details
 * Gives name, power, armor health, experience etc
 */
void Monster::getDetails() {
    std::cout << "Name: " << getName() << "\n" <<
              "Type: " << getType() << "\n" <<
              "HP/Max HP: " << getHealth() << "/" << getMaxHealth() <<"\n" <<
              "Power:  " << getPower() << "\n" <<
              "Armor: " << getArmor() << "\n" <<
              "Level: " << getLevel() << "\n" <<
              "Experience: " << getExperiencePoints() << "/" << getMaxExperiencePoints() << "\n" <<
              "Description: " << getDescription() << "\n" <<
              "In Roster: " << isInRoster() << "\n" <<
              "ID: " << getId() << "\n" << std::endl;
}

/**
 * Level's up a monster
 * Increases statistic by 1.5 and
 * clears current experience back to zero.
 * Increases current level and maximum experience that it needs
 * for the next level
 */
void Monster::evolve(){
    if(this->getLevel() < 3){ //currently system only supports up to 3 levels
        std::cout << this->getName() << " just evolved!" << std::endl;
        this->setPower(this->getPower() * 1.5);
        this->setMaxHealth((this->getMaxHealth() * 1.5));
        this->setHealth(this->getMaxHealth());//and heal it up
        this->setArmor(this->getArmor() * 1.5);
        this->setExperiencePoints(0);
        this->setLevel(this->getLevel() + 1);
        this->setMaxExperiencePoints(this->getMaxExperiencePoints() * this->getLevel());
    }
}

/**
 * Block heals a monster by an amount
 * if its of type "Rock", it will be healed addinational 5
 * @param amount to be healed
 */
void Monster::block(int amount){
    if (this->getType() == "Rock")amount = amount + 5;
    std::cout << "\n" << this->getName() << " blocks!\n" <<
              "Heals for " << amount << "HP "<< std::endl;
    heal(amount);
}

/**
 * Basic attack that will deal damage to the enemy monster,
 * it considers type, if weakness is found it will deal extra damage based on the
 * damageMultiplier.
 * It also considers armor (some monsters have negative armor too for addinational damage)
 * to reduce damage.
 * Minimum amount damage is always 1
 * If life goes below 0, its set back to 0 *
 * @param defendingMonster A monster that monster is attacking
 */
void Monster::basicAttack(Monster& defendingMonster){
    float damageMultiplier = 1; //Normal attack have full effect on opponent, if its weak for its type, i will receive more
    int damage;
    if(defendingMonster.getWeakness() == this->getType()){
        damageMultiplier = 1.5;                 //multiplier will always round up as I use integers, not floats, intentional design
        std::cout << "Exploited Weakness! Damage Multiplied by " << damageMultiplier;
    }

    damage = this->getPower() * damageMultiplier - defendingMonster.getArmor();
    if (damage < 1) damage = 1;                  //In case damage is negative or armor is too high, you always deal 1 damage

    defendingMonster.setHealth(defendingMonster.getHealth() - damage);
    if(defendingMonster.getHealth() < 0)defendingMonster.setHealth(0);

    std::cout << "\n" << this->getName() << " has attacked " << defendingMonster.getName() << " with "
              << defendingMonster.getArmor() << " armor for " << this->getPower() * damageMultiplier << " damage\n" <<
              "Actual damage: " << damage << "\n" <<
              defendingMonster.getName() << " has " << defendingMonster.getHealth() << "HP left\n";
}

/**
 * Creates a new Monster with (slightly) random variables
 * that are a little different based on their type.
 * Eg. Fire monsters tend to have more damage and less armor etc.
 * @param number of which monster to make
 * @return a new Monster of choice
 */
Monster *Monster::createMonster(int choice) {

    if (choice == 1){
        uniqueId++;
        return new FireMonster(uniqueId, "Fire", RandomGenerator::getRandomMonsterName(), RandomGenerator::randomValue(50,90),
                               RandomGenerator::randomValue(-2,2), RandomGenerator::randomValue(15,30), 1);
    }
    else if (choice == 2){
        uniqueId++;
        return new WaterMonster(uniqueId, "Water", RandomGenerator::getRandomMonsterName(), RandomGenerator::randomValue(50, 130),
                                RandomGenerator::randomValue(0, 3), RandomGenerator::randomValue(12, 25), 1);
    }
    else if (choice == 3){
        uniqueId++;
        return new RockMonster(uniqueId, "Rock", RandomGenerator::getRandomMonsterName(), RandomGenerator::randomValue(80, 180),
                               RandomGenerator::randomValue(2, 8), RandomGenerator::randomValue(8, 20), 1);
    }
}

/**
 * Creates a new Monster with (slightly) random variables
 * that are a little different based on their type.
 * Eg. Fire monsters tend to have more damage and less armor etc.
 * Opponent version doesn't get saved (by using uniqueId variable)
 * and is lost after arena match.
 * @param number of which monster to make
 * @return a new Monster of choice
 */
Monster *Monster::createOpponentMonster(int choice) {
    if (choice == 1){
        return new FireMonster(uniqueId, "Fire", RandomGenerator::getRandomMonsterName(), RandomGenerator::randomValue(50,90),
                               RandomGenerator::randomValue(-2,2), RandomGenerator::randomValue(15,25), 1);
    }
    else if (choice == 2){
        return new WaterMonster(uniqueId, "Water", RandomGenerator::getRandomMonsterName(), RandomGenerator::randomValue(50, 130),
                                RandomGenerator::randomValue(0, 3), RandomGenerator::randomValue(10, 20), 1);
    }
    else if (choice == 3){
        return new RockMonster(uniqueId, "Rock", RandomGenerator::getRandomMonsterName(), RandomGenerator::randomValue(80, 180),
                               RandomGenerator::randomValue(2, 8), RandomGenerator::randomValue(8, 20), 1);
    }
}
/**
 * Creates an "empty" monster with negative values,
 * for the purpose of the loading system.
 * @param choice Choice of which monster should be created
 * @return  new emptyMonster
 */
Monster *Monster::createEmptyMonster(int choice){
    if(choice == 1){
        return new FireMonster(-100, "", "", -100, -100, -100, -100);
    }
    else if (choice == 2){
        return new WaterMonster(-100, "", "", -100, -100, -100, -100);
    }
    else if (choice == 3){
        return new RockMonster(-100, "", "", -100, -100, -100, -100);
    }


}
//Setters
void Monster::specialAttack(Monster& defendingMonster){
}
void Monster::setHealth(int setHealthVariable) {
}
void Monster::setName(std::string name) {
}
void Monster::setInRoster(bool inRoster) {
}
void Monster::setMaxHealth(int maxHealth) {
}
void Monster::setArmor(int armor) {
}
void Monster::setPower(int power) {
}
void Monster::setExperiencePoints(int experiencePoints) {
}
void Monster::setMaxExperiencePoints(int maxExperiencePoints) {
}
void Monster::setLevel(int level) {
}
void Monster::setDescription(const std::string &description) {
}
void Monster::setId(int id) {
}
void Monster::setFainted(bool fainted){
}
void Monster::setType(const std::string &type) {
}

//Getters
std::string Monster::getName(){
    return 0;
}
int Monster::getUniqueId(){
    return uniqueId;
}
int Monster::getHealth() {
    return 0;
}
int Monster::getMaxHealth() {
    return 0;
}
int Monster::getPower() {
    return 0;
}
bool Monster::getFainted() {
    return 0;
}
int Monster::getExperiencePoints(){
    return -1;
}
int Monster::getLevel(){
    return 0;
}
int Monster::getArmor() {
    return 0;
}
std::string Monster::getType() {
    return 0;
}
int Monster::getMaxExperiencePoints(){
    return 0;
}
int Monster::getId() {
    return 0;
}
std::string Monster::getWeakness(){
    return 0;
}


bool Monster::isInRoster(){
    return 0;
}
void Monster::heal(int amountToHeal){
}
std::string Monster::getDescription(){
    return nullptr;
}