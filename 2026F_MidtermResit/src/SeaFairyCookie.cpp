#include "SeaFairyCookie.hpp"

SeaFairyCookie::SeaFairyCookie(
    std::string name,
    Element type,
    int damage,
    int defense,
    int health
    ):MiddleGingerbreadMan(name,
            type,
            damage,
            defense,
            health,
            0.3){}

void SeaFairyCookie::levelUp() {
    level+=1;
    damage+=100;
    defense+=150;
    health+=160;
    if (maxCritCount>1) {
        maxCritCount-=1;
        critCount=0;
    }
    currHealth=health;
    criticalBuff();
}

int SeaFairyCookie::attack(Element enemyType) {

    if (isCriticalHit()) {
        return(1 + critDamage + elementalAttack(enemyType)) * damage + critDamage * defense;
    }
    return (1 + elementalAttack(enemyType)) * damage + 0 * defense;
}

