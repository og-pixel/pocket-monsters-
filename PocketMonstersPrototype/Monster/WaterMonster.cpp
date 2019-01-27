#include "WaterMonster.h"
#include "../RandomGenerator.h"

//Constructor
WaterMonster::WaterMonster(int id, std::string type, std::string name, int health, int armor, int power, int level) {
    this->id = id;
    this->type = type;
    this->name = name;
    this->health = health;
    maxHealth = health;
    this->armor = armor;
    this->experiencePoints = 0;
    this->level = level;
    this->maxExperiencePoints = level * 10;
    this->power = power;
    description = RandomGenerator::createRandomDescription();
    fainted = false;
    inRoster = false;
    weakness = "Rock";
}

/**
 * Almost the same as basic attack but damage is 0.5 and can multiply up to 1.4
 * Considers armor but heals monster for 20% of total health
 * @param defendingMonster
 */
void WaterMonster::specialAttack(Monster &defendingMonster) {
    float damageMultiplier = 0.5;   //Normal attack have full effect on opponent, if it weak for its type, i will receive more
    int damage;

    if (defendingMonster.getWeakness() == this->getType()) {
        damageMultiplier = 1.4;                 //multiplier will always round up as I use integers, not floats
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
    std::cout << this->getName() << " has healed itself for: " << this->getMaxHealth() * 0.20 << "HP" << std::endl;
    this->heal(this->getMaxHealth() * 0.25);
}


/**
 * Heals a monster by the amount
 * If the amount exceeds total health, it goes to maximum instead.
 * @param amountToHeal
 */
void WaterMonster::heal(int amountToHeal) {
    setHealth(getHealth() + amountToHeal);
    if (getHealth() > getMaxHealth()) {
        setHealth(maxHealth);
    }
}

std::string WaterMonster::getName() {
    return name;
}

bool WaterMonster::isInRoster() {
    return inRoster;
}

int WaterMonster::getId() {
    return id;
}

int WaterMonster::getHealth() {
    return health;
}

int WaterMonster::getMaxHealth() {
    return maxHealth;
}

int WaterMonster::getPower() {
    return power;
}

bool WaterMonster::getFainted() {
    return fainted;
}

int WaterMonster::getExperiencePoints() {
    return experiencePoints;
}

int WaterMonster::getLevel() {
    return level;
}

int WaterMonster::getArmor() {
    return armor;
}

std::string WaterMonster::getType() {
    return type;
}

std::string WaterMonster::getWeakness() {
    return weakness;
}

std::string WaterMonster::getDescription() {
    return description;
}

int WaterMonster::getMaxExperiencePoints() {
    return maxExperiencePoints;
}

void WaterMonster::setId(int id) {
    WaterMonster::id = id;
}

void WaterMonster::setType(const std::string &type) {
    WaterMonster::type = type;
}

void WaterMonster::setMaxHealth(int maxHealth) {
    WaterMonster::maxHealth = maxHealth;
}

void WaterMonster::setArmor(int armor) {
    WaterMonster::armor = armor;
}

void WaterMonster::setFainted(bool fainted) {
    WaterMonster::fainted = fainted;
}

void WaterMonster::setPower(int power) {
    WaterMonster::power = power;
}

void WaterMonster::setExperiencePoints(int experiencePoints) {
    WaterMonster::experiencePoints = experiencePoints;
}

void WaterMonster::setLevel(int level) {
    WaterMonster::level = level;
}

void WaterMonster::setMaxExperiencePoints(int maxExperiencePoints) {
    WaterMonster::maxExperiencePoints = maxExperiencePoints;
}

void WaterMonster::setDescription(const std::string &description) {
    WaterMonster::description = description;
}

void WaterMonster::setInRoster(bool inRoster) {
    WaterMonster::inRoster = inRoster;
}

void WaterMonster::setHealth(int x) {
    health = x;
}

void WaterMonster::setName(std::string name) {
    WaterMonster::name = name;
}

