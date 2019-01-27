#include "RockMonster.h"
#include "../RandomGenerator.h"


RockMonster::RockMonster(int id, std::string type, std::string name, int health, int armor, int power, int level) {
    this->id = id;
    this->type = type;
    this->name = name;
    this->health = health;
    maxHealth = health;
    this->armor = armor;
    experiencePoints = 0;
    this->level = level;
    this->maxExperiencePoints = level * 10;
    this->power = power;
    description = RandomGenerator::createRandomDescription();
    fainted = false;
    inRoster = false;
    weakness = "Fire";
}

/**
 * Damage is 2 and can multiply up to 3
 * Considers armor but heals monster self harm monster by
 * 0.5 of its power
 * @param defendingMonster
 */
void RockMonster::specialAttack(Monster &defendingMonster) {
    float damageMultiplier = 2;   //Normal attack have full effect on opponent, if it weak for its type, i will receive more
    int damage;

    if (defendingMonster.getWeakness() == this->getType()) {
        damageMultiplier = 3;                 //multiplier will always round up as I use integers, not floats
        std::cout << "Exploited Weakness! Damage Multiplied by " << damageMultiplier;
    }

    damage = this->getPower() * damageMultiplier - defendingMonster.getArmor();
    if (damage < 1) damage = 1; //In case damage is negative or armor is too high, you always deal 1 damage

    defendingMonster.setHealth(defendingMonster.getHealth() - damage);
    if (defendingMonster.getHealth() < 0)defendingMonster.setHealth(0);

    std::cout << "\n" << this->getName() << " has attacked " << defendingMonster.getName() << " with "
              << defendingMonster.getArmor() << " armor for " << this->getPower() * damageMultiplier << " damage\n" <<
              "Actual damage: " << damage << "\n" <<
              defendingMonster.getName() << " has " << defendingMonster.getHealth() << "HP left\n";
    std::cout << this->getName() << " damages itself for: " << this->getPower() * 0.5 << " damage" << std::endl;

    this->setHealth(this->getHealth() - (this->getPower() * 0.5));
}

/**
 * Heals a monster by the amount
 * If the amount exceeds total health, it goes to maximum instead.
 * @param amountToHeal
 */
void RockMonster::heal(int amountToHeal) {
    setHealth(getHealth() + amountToHeal);
    if (getHealth() > getMaxHealth()) {
        setHealth(maxHealth);
    }
}


std::string RockMonster::getName() {
    return name;
}

bool RockMonster::isInRoster() {
    return inRoster;
}

int RockMonster::getId() {
    return id;
}

int RockMonster::getHealth() {
    return health;
}

int RockMonster::getMaxHealth() {
    return maxHealth;
}

int RockMonster::getPower() {
    return power;
}

bool RockMonster::getFainted() {
    return fainted;
}

int RockMonster::getExperiencePoints() {
    return experiencePoints;
}

int RockMonster::getLevel() {
    return level;
}

int RockMonster::getArmor() {
    return armor;
}

std::string RockMonster::getType() {
    return type;
}

std::string RockMonster::getWeakness() {
    return weakness;
}

std::string RockMonster::getDescription() {
    return description;
}

int RockMonster::getMaxExperiencePoints() {
    return maxExperiencePoints;
}

void RockMonster::setId(int id) {
    RockMonster::id = id;
}

void RockMonster::setType(const std::string &type) {
    RockMonster::type = type;
}

void RockMonster::setMaxHealth(int maxHealth) {
    RockMonster::maxHealth = maxHealth;
}

void RockMonster::setArmor(int armor) {
    RockMonster::armor = armor;
}

void RockMonster::setFainted(bool fainted) {
    RockMonster::fainted = fainted;
}

void RockMonster::setPower(int power) {
    RockMonster::power = power;
}

void RockMonster::setExperiencePoints(int experiencePoints) {
    RockMonster::experiencePoints = experiencePoints;
}

void RockMonster::setLevel(int level) {
    RockMonster::level = level;
}

void RockMonster::setMaxExperiencePoints(int maxExperiencePoints) {
    RockMonster::maxExperiencePoints = maxExperiencePoints;
}

void RockMonster::setDescription(const std::string &description) {
    RockMonster::description = description;
}

void RockMonster::setInRoster(bool inRoster) {
    RockMonster::inRoster = inRoster;
}

void RockMonster::setHealth(int x) {
    health = x;
}

void RockMonster::setName(std::string name) {
    RockMonster::name = name;
}
