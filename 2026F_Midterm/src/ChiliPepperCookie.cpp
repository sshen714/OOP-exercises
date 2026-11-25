#include "ChiliPepperCookie.hpp"

ChiliPepperCookie::ChiliPepperCookie(
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

void ChiliPepperCookie::levelUp() {
    level+=1;
    damage+=100;
    defense+=100;
    health+=100;
    currHealth = health;
    criticalBuff();
}

int ChiliPepperCookie::attack(Element enemyType) {

    float crit=0;
    if (countCritTime()) {
        crit=critDamage;
    }
    return (1 + crit + currHealth / health + elementalAttack(enemyType)) * damage ;

}

bool ChiliPepperCookie::attacked(int incomingDamage) {

    int realDamage = incomingDamage - defense;
    if (countAvoidTime() || realDamage <= 0) {
        return true;
    }
    currHealth -=realDamage;
    return false;

}