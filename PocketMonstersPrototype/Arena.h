#include <vector>
#include "Monster/Monster.h"
#include "RandomGenerator.h"
#include "Menu.h"

class Arena {
public:
    Arena(int rosterSize, int difficulty, int monsterLevel);
    //public because i was too lazy to make getters and setters, horrible long variables
    std::vector<Monster *> playerMonsterRoster; //Player team
    std::vector<Monster *> enemyMonsterRoster;  //Opponent team
    int activePlayerMonster = 0;
    int activeEnemyMonster = 0;
    bool checkConditions();
    void drawArena();
    void drawCombatStatus();
    void drawControls();
    void changeActiveMonster();

    int healSwappingLimit = 0;

    int getActivePlayerMonster();
    int getActiveEnemyMonster();

    void setActivePlayerMonster(int activePlayerMonster);
    void setActiveEnemyMonster(int activeEnemyMonster);



    void makeDecision(int difficulty);
    void makeDecision();
    void makeRandomDecision();
    void doBasicAttack();
    void doSpecialAttack();
    void doHeal();
    void swapMonster();

    void swapMonsterRandomly();
private:
    int difficultyLevel;
    int goldReward;
    int expReward;
};
