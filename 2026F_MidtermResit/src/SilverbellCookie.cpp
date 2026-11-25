#include "SilverbellCookie.hpp"

SilverbellCookie::SilverbellCookie(
    std::string name,
    Element type ,
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

void SilverbellCookie::levelUp() {
    level+=1;
    damage+=150;
    defense+=50;
    health+=150;
    currHealth=health;
    keepHealingBuff();
}

bool SilverbellCookie::onHit(int incomingDamage) {

    int check=incomingDamage - defense * (1 + level / 100.0);
    if (isDodged()||check<=0) {
        return true;
    }
    currHealth-=check;
    return false;
}