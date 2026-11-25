#include "WhiteLilyCookie.hpp"
#include "MillennialTreeCookie.hpp"

WhiteLilyCookie::WhiteLilyCookie(
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

void WhiteLilyCookie::levelUp() {
    level+=1;
    damage+=100;
    defense+=100;
    health+=100;
    currHealth = health;
}

int WhiteLilyCookie::attack(Element enemyType) {

    float crit=0;
    if (countCritTime()) {
        crit=critDamage;
    }
    return (1 + crit + elementalAttack(enemyType)) * damage + crit * currHealth ;
}

bool WhiteLilyCookie::attacked(int incomingDamage) {

    int realDamage = incomingDamage - (defense + damage);
    criticalBuff();

    if (countAvoidTime() || realDamage <= 0) {
        return true;
    }
    currHealth -=realDamage;
    return false;
}