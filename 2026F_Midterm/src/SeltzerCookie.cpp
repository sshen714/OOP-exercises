#include "SeltzerCookie.hpp"

SeltzerCookie::SeltzerCookie(
    std::string name,
    Element type,
    int damage,
    int defense,
    int health,
    float critDamage,
    int critTime,
    int avoidTime
    ):BackGingerbreadMan(name,
        type,
        damage,
        defense,
        health,
        critDamage,
        critTime,
        avoidTime){}

void SeltzerCookie::levelUp() {
    level+=1;
    damage+=100;
    defense+=100;
    health+=100;
    currHealth = health;
}

int SeltzerCookie::attack(Element enemyType) {

    float crit=0;
    if (countCritTime()) {
        crit=critDamage;
    }
    return (1 + crit + elementalAttack(enemyType)) * damage;

}

bool SeltzerCookie::attacked(int incomingDamage) {

    int realDamage = incomingDamage - defense * (1 + level / 100.0);
    keepHealingBuff();
    if (countAvoidTime() || realDamage <= 0) {
        return true;
    }
    currHealth -=realDamage;
    keepHealingBuff();
    return false;

}