#include "SilverbellCookie.hpp"

SilverbellCookie::SilverbellCookie(
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

void SilverbellCookie::levelUp() {
    level+=1;
    damage+=150;
    defense+=50;
    health+=100;
    currHealth = health;
    keepHealingBuff();
}

int SilverbellCookie::attack(Element enemyType) {

    float crit = 0;
    if (countCritTime()) {
        crit=critDamage;
    }
    return (1 + crit + elementalAttack(enemyType)) * damage ;

}

bool SilverbellCookie::attacked(int incomingDamage) {

    int realDamage = incomingDamage - defense * (1 + level / 100.0);

    if (countAvoidTime() || realDamage <= 0) {
        return true;
    }
    currHealth -=realDamage;
    return false;
}