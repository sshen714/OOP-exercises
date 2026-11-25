#include "MillennialTreeCookie.hpp"


MillennialTreeCookie::MillennialTreeCookie(
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
        avoidTime) {}

void MillennialTreeCookie::levelUp() {
    level+=1;
    damage+=150;
    defense+=150;
    health+=150;
    currHealth = health;
}

int MillennialTreeCookie::attack(Element enemyType) {

    float crit = 0;
    if (countCritTime()) {
        crit=critDamage;
    }
    return (1 + crit + currHealth / health + elementalAttack(enemyType)) * damage ;

}

bool MillennialTreeCookie::attacked(int incomingDamage) {
    
    int realDamage = incomingDamage - defense * (1 + currHealth / health);
    defenseBuff();
    if (countAvoidTime() || realDamage <= 0) {
        return true;
    }
    currHealth -=realDamage;
    return false;

}