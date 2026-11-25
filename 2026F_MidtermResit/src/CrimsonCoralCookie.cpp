#include "CrimsonCoralCookie.hpp"

CrimsonCoralCookie::CrimsonCoralCookie(
    std::string name,
    Element type,
    int damage ,
    int defense ,
    int health
    ):FrontGingerbreadMan(name,
        type,
        damage,
        defense,
        health,
        0.5,
        5,
        10){}

int CrimsonCoralCookie::attack(Element enemyType) {

    int crit =0;
    if (isCriticalHit()) {
        crit =(1 + critDamage + elementalAttack(enemyType)) * damage + defense + health ;
        defenseBuff();
        return crit;
    }
    crit=(1 + elementalAttack(enemyType)) * damage + defense + health ;
    defenseBuff();
    return crit;

}