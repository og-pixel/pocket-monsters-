#include "FireMonster.h"
#include "../RandomGenerator.h"


FireMonster::FireMonster(int id, std::string type, std::string name, int health, int armor, int power, int level) {
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
    weakness = "Water";
}


/**
 * Damage is 1.5 and can multiply up to 2
 * Ignores armor
 * @param defendingMonster
 */
void FireMonster::specialAttack(Monster& defendingMonster){
    float damageMultiplier = 1.5;   //Normal attack have full effect on opponent, if it weak for its type, i will receive more
    int damage;

    if(defendingMonster.getWeakness() == this->getType()){
        damageMultiplier = 2;                 //multiplier will always round up as I use integers, not floats
        std::cout << "Exploited Weakness! Damage Multiplied by " << damageMultiplier;
    }

    damage = this->getPower() * damageMultiplier;
    if (damage < 1) damage = 1; //In case damage is negative or armor is too high, you always deal 1 damage

    defendingMonster.setHealth(defendingMonster.getHealth() - damage);
    if(defendingMonster.getHealth() < 0)defendingMonster.setHealth(0);

    std::cout << "\n" << this->getName() << " has attacked " << defendingMonster.getName() << " with "
              << defendingMonster.getArmor() << " armor(Ignored) for " << this->getPower() * damageMultiplier << " damage\n" <<
              "Actual damage: " << damage << "\n" <<
              defendingMonster.getName() << " has " << defendingMonster.getHealth() << "HP left\n";
}

/**
 * Heals a monster by the amount
 * If the amount exceeds total health, it goes to maximum instead.
 * @param amountToHeal
 */
void FireMonster::heal(int amountToHeal){
    setHealth(getHealth() + amountToHeal);
    if(getHealth() > getMaxHealth()){
        setHealth(maxHealth);
    }
}


std::string FireMonster::getName() {
    return name;
}

bool FireMonster::isInRoster() {
    return inRoster;
}

int FireMonster::getId() {
    return id;
}

int FireMonster::getHealth() {
    return health;
}

int FireMonster::getMaxHealth() {
    return maxHealth;
}

int FireMonster::getPower() {
    return power;
}

bool FireMonster::getFainted() {
    return fainted;
}

int FireMonster::getExperiencePoints() {
    return experiencePoints;
}

int FireMonster::getLevel() {
    return level;
}

int FireMonster::getArmor() {
    return armor;
}

std::string FireMonster::getType() {
    return type;
}

std::string FireMonster::getWeakness() {
    return weakness;
}

std::string FireMonster::getDescription() {
    return description;
}

int FireMonster::getMaxExperiencePoints() {
    return maxExperiencePoints;
}

void FireMonster::setId(int id) {
    FireMonster::id = id;
}

void FireMonster::setType(const std::string &type) {
    FireMonster::type = type;
}

void FireMonster::setMaxHealth(int maxHealth) {
    FireMonster::maxHealth = maxHealth;
}

void FireMonster::setArmor(int armor) {
    FireMonster::armor = armor;
}

void FireMonster::setFainted(bool fainted) {
    FireMonster::fainted = fainted;
}

void FireMonster::setPower(int power) {
    FireMonster::power = power;
}

void FireMonster::setExperiencePoints(int experiencePoints) {
    FireMonster::experiencePoints = experiencePoints;
}

void FireMonster::setLevel(int level) {
    FireMonster::level = level;
}

void FireMonster::setMaxExperiencePoints(int maxExperiencePoints) {
    FireMonster::maxExperiencePoints = maxExperiencePoints;
}

void FireMonster::setDescription(const std::string &description) {
    FireMonster::description = description;
}

void FireMonster::setInRoster(bool inRoster) {
    FireMonster::inRoster = inRoster;
}

void FireMonster::setHealth(int x) {
    health = x;
}

void FireMonster::setName(std::string name) {
    FireMonster::name = name;
}



