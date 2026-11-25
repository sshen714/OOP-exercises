#include "FireSpiritCookie.hpp"

FireSpiritCookie::FireSpiritCookie(
    std::string name,
    Element type,
    int damage,
    int defense,
    int health,
    float critDamage,
    int maxCritCount,
    int maxDodgeCount
    ):BackGingerbreadMan(name,
        type,
        damage,
        defense,
        health,
        critDamage,
        maxCritCount,
        maxDodgeCount){}

void FireSpiritCookie::levelUp() {

    level+=1;
    damage+=100;
    critDamage+=0.1;
    defense+=5;
    health+=20;
    currHealth=health;
    keepHealingBuff();
}