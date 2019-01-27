#include "Arena.h"


//Arena Constructor
Arena::Arena(int rosterSize, int difficulty, int monsterLevel) {
    //Create an enemy team of the equal size
    for (int i = 0; i < rosterSize; i++) {
        enemyMonsterRoster.push_back(Monster::createOpponentMonster(
                RandomGenerator::randomValue(1, 3)));
    }
    //"Evolve" an enemy team of the chosen level
    for(int i = 0; i < monsterLevel - 1; i++) {
        for (int x = 0; x < enemyMonsterRoster.size(); x++) {
            enemyMonsterRoster[x]->evolve();
        }
    }

    expReward = (rosterSize * 5) * monsterLevel;                        //Experience reward for individual monsters
    goldReward = (100 * difficulty * monsterLevel) + (rosterSize * 50); //Reward for winning
    difficultyLevel = difficulty;                                       //"AI" skill

    //Add monsters from monster list that are going to roster
    for (int i = 0; i < Player::monsterList.size(); i++) {
        if (Player::monsterList[i]->isInRoster()) {
            playerMonsterRoster.push_back(Player::monsterList[i]);
        }
    }
}
/**
 * Start menu where player has a chance to see enemy team
 * and either join the fray or concede
 * It will immediately check if all player's monsters are fainted in to stop the game
 */
void Arena::drawArena() {
    //At start active monster is always the one in position 0
    Menu::clear;
    drawCombatStatus();
    std::cout << "\n\nWould you like to start?\n" <<
              "1) Start\n" <<
              "0) Concede" << std::endl;

    int choice;
    std::cin >> choice;
    if (choice == 1) {
        Menu::clear();
        if (checkConditions())return;
        drawCombatStatus();
        drawControls();
    } else if (choice == 0) {
        std::cout << "You Concede!" << std::endl;
        Menu::clear();
        return;
    } else {
        Menu::clear();
        drawArena();
    }
}

/**
 * Part of the Combat system which displays enemy's and player's
 * Combat stats, such as level, health, power, armor
 * Also checks which monster is "active" (eg the one fighting at the moment)
 * and Checks if a monster has fainted (is unable to fight anymore)
 */
void Arena::drawCombatStatus() {
    std::cout << "*********************************" << std::endl;
    std::cout << "Your Team: " << std::endl;
    for (int i = 0; i < playerMonsterRoster.size(); i++) {
        std::cout << playerMonsterRoster[i]->getName() << " "
                  << playerMonsterRoster[i]->getType() <<
                  " Power:" << playerMonsterRoster[i]->getPower() << " "
                          "Lvl:" << playerMonsterRoster[i]->getLevel() << " "
                          "Armor:" << playerMonsterRoster[i]->getArmor() << " "
                  << playerMonsterRoster[i]->getHealth() << "/" << playerMonsterRoster[i]->getMaxHealth() << "HP";
        if (i == getActivePlayerMonster()) { std::cout << " ACTIVE"; }
        if (playerMonsterRoster[i]->getFainted()) { std::cout << " FAINTED"; }
        std::cout << std::endl;
    }
    std::cout << "*********************************" << std::endl;
    std::cout << "Enemy Team: " << std::endl;
    for (int i = 0; i < enemyMonsterRoster.size(); i++) {
        std::cout << enemyMonsterRoster[i]->getName() << " "
                  << enemyMonsterRoster[i]->getType() <<
                  " Power:" << enemyMonsterRoster[i]->getPower() << " "
                          "Lvl:" << enemyMonsterRoster[i]->getLevel() << " "
                          "Armor:" << enemyMonsterRoster[i]->getArmor() << " "
                  << enemyMonsterRoster[i]->getHealth() << "/" << enemyMonsterRoster[i]->getMaxHealth() << "HP";
        if (i == getActiveEnemyMonster()) { std::cout << " ACTIVE"; }
        if (enemyMonsterRoster[i]->getFainted()) { std::cout << " FAINTED"; }
        std::cout << std::endl;
    }
    std::cout << "*********************************" << std::endl;
}

/**
 * Draws Control system which lets the user to
 * fight with the opponent,
 * monsters have basic attack, unique special attack
 * they can also "block" (which heals them).
 * You can also (and have to if active monster has fainted)
 * swap active monster
 * and use items.
 * All of which consumes "a turn"
 * Which in this game is just an passing a method
 * makeDecision() which decides what to do.
 */
void Arena::drawControls() {
    std::cout << "\nOptions\n" <<
              "All actions affect active monster\n" <<
              "One action per turn\n\n" <<
              "1) Basic Attack\n" <<
              "2) Special Attack\n" <<
              "3) Block(Heal 5HP)\n" <<
              "4) Choose Active Monster\n" <<
              "5) Use Item\n" <<
              "0) Concede" << std::endl;

    int choice;
    std::cin >> choice;
    if (choice == 1 && !playerMonsterRoster[getActivePlayerMonster()]->getFainted()) {
        Menu::clear();
        playerMonsterRoster[getActivePlayerMonster()]->basicAttack(*enemyMonsterRoster[getActiveEnemyMonster()]);
        if (checkConditions())return;
        makeDecision(difficultyLevel);
        if (checkConditions())return;
        drawCombatStatus();
        drawControls();
    } else if (choice == 2 && !playerMonsterRoster[getActivePlayerMonster()]->getFainted()) {
        Menu::clear();
        playerMonsterRoster[getActivePlayerMonster()]->specialAttack(*enemyMonsterRoster[getActiveEnemyMonster()]);
        if (checkConditions())return;
        makeDecision(difficultyLevel);
        if (checkConditions())return;
        drawCombatStatus();
        drawControls();
    } else if (choice == 3 && !playerMonsterRoster[getActivePlayerMonster()]->getFainted()) {
        Menu::clear();
        playerMonsterRoster[getActivePlayerMonster()]->block(5);
        if (checkConditions())return;
        makeDecision(difficultyLevel);
        if (checkConditions())return;
        drawCombatStatus();
        drawControls();
    } else if (choice == 4) {
        changeActiveMonster();
    } else if (choice == 5 && !playerMonsterRoster[getActivePlayerMonster()]->getFainted()) {
        int itemChoice;
        itemChoice = Player::displayBackpackContentForArena();

        if (itemChoice != -1) {
            if (Player::backpack[itemChoice]->getTargetsAlly()) { //If item targets your monsters
                Menu::clear();
                Player::backpack[itemChoice]->useItem(*playerMonsterRoster[activePlayerMonster]);
                Player::backpack.erase(Player::backpack.begin() + itemChoice);
                if (checkConditions())return;
                makeDecision(difficultyLevel);
                if (checkConditions())return;
                drawCombatStatus();
                drawControls();
            } else {                                               //If item targets enemy monsters
                Menu::clear();
                Player::backpack[itemChoice]->useItem(*enemyMonsterRoster[activeEnemyMonster]);
                Player::backpack.erase(Player::backpack.begin() + itemChoice);
                if (checkConditions())return;
                makeDecision(difficultyLevel);
                if (checkConditions())return;
                drawCombatStatus();
                drawControls();
            }
        } else {
            drawCombatStatus();
            drawControls();
        }
    } else if (choice == 0) {
        std::cout << "You conceded!" << std::endl;
        Menu::clear();
        return;
    } else {
        Menu::clear();
        drawCombatStatus();
        drawControls();
    }
}

/**
 * As a part of the combat, player can change
 * active monster (and have to when active one has fainted).
 * They cannot change to the one that has already fainted.
 */
void Arena::changeActiveMonster() {
    Menu::clear();
    for (int i = 0; i < playerMonsterRoster.size(); i++) {
        std::cout << i + 1 << ") "
                  << playerMonsterRoster[i]->getName() << " "
                  << playerMonsterRoster[i]->getType() <<
                  " Power:" << playerMonsterRoster[i]->getPower() << " "
                          "Lvl:" << playerMonsterRoster[i]->getLevel() << " "
                          "Armor:" << playerMonsterRoster[i]->getArmor() << " "
                  << playerMonsterRoster[i]->getHealth() << "/" << playerMonsterRoster[i]->getMaxHealth() << "HP";
        if (i == getActivePlayerMonster()) { std::cout << " ACTIVE"; }
        if (playerMonsterRoster[i]->getFainted()) { std::cout << " FAINTED"; }
        std::cout << std::endl;
    }
    std::cout << "\nWhich monster you'd like to swap?\n" <<
              "If you choose the same one, it wont consume the turn" << std::endl;
    int choice;
    std::cin >> choice;
    Menu::clear();
    if (choice - 1 != getActivePlayerMonster() && choice <= playerMonsterRoster.size() &&
        !playerMonsterRoster[choice - 1]->getFainted()) {
        std::cout << "Changed active monster!" << std::endl;
        setActivePlayerMonster(choice - 1);
        if (checkConditions())return;
        makeDecision(difficultyLevel);
        if (checkConditions())return;
        drawCombatStatus();
        drawControls();
    } else {
        std::cout << "NOT changed active monster\n"
                "Remember you cannot swap monsters that have fainted" << std::endl;
        drawCombatStatus();
        drawControls();
    }
}


/**
 * Method ran after each turn to check if a game should end
 * Main win condition is if all monsters in rotation are "fainted"
 * If player wins, they get rewards in gold and experience for monsters
 * And if monster's experience raises above limit, it will evolve
 * There is also 3 in 10 chance to find a new monster.
 * @return true if you either lose or win the game(used to exit arena), return false otherwise
 */
bool Arena::checkConditions() {
    int playerMonstersFainted = 0;
    int enemyMonstersFainted = 0;

    for (int i = 0; i < playerMonsterRoster.size(); i++) {
        if (playerMonsterRoster[i]->getHealth() <= 0) {
            playerMonsterRoster[i]->setFainted(true);
        }
    }

    for (int i = 0; i < enemyMonsterRoster.size(); i++) {
        if (enemyMonsterRoster[i]->getHealth() <= 0) {
            enemyMonsterRoster[i]->setFainted(true);
        }
    }


    for (int i = 0; i < playerMonsterRoster.size(); i++) {
        if (playerMonsterRoster[i]->getFainted()) {
            playerMonstersFainted++;
        }
    }

    for (int i = 0; i < enemyMonsterRoster.size(); i++) {
        if (enemyMonsterRoster[i]->getFainted()) {
            enemyMonstersFainted++;
        }
    }

    //final test, if entire team is fainted, you either win or lose
    if (playerMonstersFainted >= playerMonsterRoster.size()) {
        std::cout << "YOU LOST" << std::endl;

        for (int i = 0; i < playerMonsterRoster.size(); i++) {
            playerMonsterRoster[i]->setFainted(false);
        }
        return true;
    }

    if (enemyMonstersFainted >= enemyMonsterRoster.size()) {
        std::cout << "YOU WIN" << std::endl;
        std::cout << "You have earned: " << goldReward << "gold!\n"
                "And " << expReward << " experience for each monster fighting!" << std::endl;
        Player::setGold(Player::getGold() + goldReward);

        for (int i = 0; i < playerMonsterRoster.size(); i++) {
            playerMonsterRoster[i]->setExperiencePoints(playerMonsterRoster[i]->getExperiencePoints() + expReward);
            if (playerMonsterRoster[i]->getExperiencePoints() >= playerMonsterRoster[i]->getMaxExperiencePoints()) {
                playerMonsterRoster[i]->evolve();
            }
        }

        for (int i = 0; i < playerMonsterRoster.size(); i++) {
            playerMonsterRoster[i]->setFainted(false);
        }

        if (RandomGenerator::randomValue(1, 10) > 7) {
            std::cout << "You have found a monster!" << std::endl;
            std::cout << "Check Your Monster list for more info!" << std::endl;
            Player::monsterList.push_back(Monster::createMonster(RandomGenerator::randomValue(1, 3)));
        }
        return true;
    }
    return false;
}

//Getters
int Arena::getActivePlayerMonster() {
    return activePlayerMonster;
}
int Arena::getActiveEnemyMonster() {
    return activeEnemyMonster;
}
//Setters
void Arena::setActivePlayerMonster(int activePlayerMonster) {
    Arena::activePlayerMonster = activePlayerMonster;
}
void Arena::setActiveEnemyMonster(int activeEnemyMonster) {
    Arena::activeEnemyMonster = activeEnemyMonster;
}

/**
 * Chooses AI MODE
 * Either random one or "smarter" one
 * */
void Arena::makeDecision(int difficulty) {
    std::cout << "Enemy makes decision\n"
            "***********************\n";
    if (difficulty == 1)makeRandomDecision();
    else makeDecision();
}

/**
 * Pseudo random decision, extra condition checks if monster is fainted, as they cannot fight
 * It will also be FORCED to swap if current monster fainted.
 */
void Arena::makeRandomDecision() {
    int diceRoll;
    diceRoll = RandomGenerator::randomValue(1, 100);    //to make easy % chances

    if (diceRoll <= 40 && !enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        doBasicAttack();
    } else if (diceRoll > 40 && diceRoll < 66 && !enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        doSpecialAttack();
    } else if (diceRoll > 66 && diceRoll < 91 && !enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        doHeal();
    } else if ((diceRoll > 91 && diceRoll < 100) || enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        swapMonsterRandomly();
    }
}


/**
 * Order means priority too,
 * it wont bother checking other conditions
 * if a top one is true already
 * AI is super smart, just a bunch of if statments,
 * It doesn't consider all factors etc.
 */
void Arena::makeDecision() {

    //If player's monster has low health
    if (playerMonsterRoster[activePlayerMonster]->getHealth() <=
        playerMonsterRoster[activePlayerMonster]->getHealth() * 0.25 && !enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        //if type is NOT water, basic attack
        if (enemyMonsterRoster[activeEnemyMonster]->getType() != "Water") {
            doBasicAttack();
        }
            //Otherwise special!
        else {
            doSpecialAttack();
        }
        if (healSwappingLimit > 0)healSwappingLimit--;
        return;
    }

    //If health is below 35%
    if (enemyMonsterRoster[activeEnemyMonster]->getHealth() <=
        enemyMonsterRoster[activeEnemyMonster]->getMaxHealth() * 0.35
        && healSwappingLimit < 4 && !enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        //if type is water, special attack
        if (enemyMonsterRoster[activeEnemyMonster]->getType() == "Water") {
            doSpecialAttack();
        }
            //Otherwise, heal!
        else {
            doHeal();
            healSwappingLimit++;
        }
        return;
    }
    //If health is below 25% AND there are monsters to swap (doesn't consider if they have low health too)
    if ((enemyMonsterRoster[activeEnemyMonster]->getHealth() <
         enemyMonsterRoster[activeEnemyMonster]->getMaxHealth() * 0.25)
        && enemyMonsterRoster.size() > 1 && healSwappingLimit < 4 && !enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        swapMonsterRandomly();
        healSwappingLimit++;
        return;
    }


    //All other Roll dice, a little bit more loaded towards attacking
    int diceRoll;
    diceRoll = RandomGenerator::randomValue(1, 100);    //to make easy % chances

    if (diceRoll <= 50 && !enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        doBasicAttack();
        if (healSwappingLimit > 0)healSwappingLimit--;
        return;
    } else if (diceRoll > 50 && diceRoll < 76 && !enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        doSpecialAttack();
        if (healSwappingLimit > 0)healSwappingLimit--;
        return;
    } else if (diceRoll > 76 && diceRoll < 91 && !enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        doHeal();
        return;
    } else if ((diceRoll > 91 && diceRoll < 100) || enemyMonsterRoster[activeEnemyMonster]->getFainted()) {
        swapMonsterRandomly();
        return;
    }
}

/**
 * METHODS FOR AI TO USE
 */
void Arena::doBasicAttack() {
    enemyMonsterRoster[activeEnemyMonster]->basicAttack(*playerMonsterRoster[activePlayerMonster]);
}
/**
 * METHODS FOR AI TO USE
 */
void Arena::doSpecialAttack() {
    enemyMonsterRoster[activeEnemyMonster]->specialAttack(*playerMonsterRoster[activePlayerMonster]);
}
/**
 * METHODS FOR AI TO USE
 */
void Arena::doHeal() {
    enemyMonsterRoster[activeEnemyMonster]->block(5);
}
/**
 * METHODS FOR AI TO USE
 * First checks if all monsters have fainted,
 * if yes just break as it will cause game to end anyway.
 * If not keep rolling a random number that is no an active monster
 * and is not fainted
 */
void Arena::swapMonsterRandomly() {
    //If a randomly chosen monster isn't dead AND isn't the one already in play
    int allFainted = 0;
    for (int i = 0; i < enemyMonsterRoster.size(); i++) {
        if (enemyMonsterRoster[i]->getFainted()) {
            allFainted++;
        }
        if (allFainted >= enemyMonsterRoster.size()) {
            return;
        }
    }
    while (true) {
        int newSwap = RandomGenerator::randomValue(1, enemyMonsterRoster.size());   //slighly inneficient, it will randomly chose numbers
        if (!enemyMonsterRoster[newSwap - 1]->getFainted() && enemyMonsterRoster[activeEnemyMonster]) {    //until its the one within monsterRoster range, and isn't one already active
            setActiveEnemyMonster(newSwap - 1);                                     //Its all because maximum roster size is 3
            break;
        }
    }
}

