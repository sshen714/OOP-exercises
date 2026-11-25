#include "SeaFairyCookie.hpp"

SeaFairyCookie::SeaFairyCookie(
    std::string name,
    Element type,
    int damage,
    int defense,
    int health,
    float critDamage,
    int critTime,
    int avoidTime
    ):MiddleGingerbreadMan(name,
        type,
        damage,
        defense,
        health,
        critDamage,
        critTime,
        avoidTime){}

void SeaFairyCookie::levelUp() {
    level+=1;
    damage+=100;
    defense+=200;
    health+=140;
    currHealth = health;
    criticalBuff();
}

int SeaFairyCookie::attack(Element enemyType) {

    float crit=0;
    if (countCritTime()) {
        crit=critDamage;
    }
    return (1 + crit + elementalAttack(enemyType)) * damage + crit * defense;

}

bool SeaFairyCookie::attacked(int incomingDamage) {

    int realDamage = incomingDamage - defense;
    if (countAvoidTime() || realDamage <= 0) {
        return true;
    }
    currHealth -=realDamage;
    return false;

}