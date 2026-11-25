#include "WhiteLilyCookie.hpp"

WhiteLilyCookie::WhiteLilyCookie()
:MiddleGingerbreadMan("White Lily Cookie",
        Element::Plant,
        100,
        100,
        1500,
        0.2,
        2){}


int  WhiteLilyCookie::attack(Element enemyType) {

    if (isCriticalHit()) {
        return(1 + critDamage + elementalAttack(enemyType)) * damage + critDamage * currHealth;
    }
    return (1 + elementalAttack(enemyType)) * damage + 0 * currHealth;
}

bool WhiteLilyCookie::onHit(int incomingDamage) {

    int check=incomingDamage - (defense + damage);
    criticalBuff();
    if (isDodged()||check<=0) {
        return true;
    }
    currHealth-=check;
    return false;
}