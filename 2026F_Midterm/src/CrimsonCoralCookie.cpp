#include "CrimsonCoralCookie.hpp"

CrimsonCoralCookie::CrimsonCoralCookie(
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


void CrimsonCoralCookie::levelUp() {
    level+=1;
    damage+=100;
    defense+=100;
    health+=100;
    currHealth = health;
}

int CrimsonCoralCookie::attack(Element enemyType) {

    float crit=0;
    if (countCritTime()) {
        crit=critDamage;
    }
    float attack=(1 + crit + elementalAttack(enemyType)) * damage + defense + health;
    defenseBuff();
    return attack;
}

bool CrimsonCoralCookie::attacked(int incomingDamage) {

    int realDamage = incomingDamage - defense;
    if (countAvoidTime() || realDamage <= 0) {
        return true;
    }
    currHealth -=realDamage;
    return false;

}