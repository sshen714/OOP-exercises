#include "FireSpiritCookie.hpp"

FireSpiritCookie::FireSpiritCookie(
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

void FireSpiritCookie::levelUp() {
    level+=1;
    damage+=100;
    health+=10;
    critDamage+=0.1;
    currHealth = health;
    keepHealingBuff();
}

int FireSpiritCookie::attack(Element enemyType) {

    float crit=0;
    if (countCritTime()) {
        crit=critDamage;
    }
    return (1 + crit + elementalAttack(enemyType)) * damage;
}

bool FireSpiritCookie::attacked(int incomingDamage) {

    int realDamage = incomingDamage - defense;

    if (countAvoidTime() || realDamage <= 0) {
        return true;
    }
    currHealth -=realDamage;
    return false;

}