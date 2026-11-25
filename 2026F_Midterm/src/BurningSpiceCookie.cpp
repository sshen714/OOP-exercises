#include "BurningSpiceCookie.hpp"

BurningSpiceCookie::BurningSpiceCookie(
    std::string name,
    Element type,
    int damage,
    int defense,
    int health,
    float critDamage,
    int critTime,
    int avoidTime
    ):FrontGingerbreadMan(name,
        type,
        damage,
        defense,
        health,
        critDamage,
        critTime,
        avoidTime){}

void BurningSpiceCookie::levelUp() {
    level+=1;
    damage+=200;
    critDamage+=0.05;
    health+=150;
    currHealth = health;
}

int BurningSpiceCookie::attack(Element enemyType) {

    float crit=0;
    if (countCritTime()) {
        crit=critDamage;
    }
    defenseBuff();
    return (1 + crit + elementalAttack(enemyType)) * damage + 50;

}

bool BurningSpiceCookie::attacked(int incomingDamage) {

    int realDamage = incomingDamage - defense;

    if (countAvoidTime() || realDamage <= 0) {
        return true;
    }
    currHealth -=realDamage;
    return false;
}