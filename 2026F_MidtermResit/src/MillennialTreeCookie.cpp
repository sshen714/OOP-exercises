#include "MillennialTreeCookie.hpp"


MillennialTreeCookie::MillennialTreeCookie(
       ):FrontGingerbreadMan("Millennial Tree Cookie",
        Element::Plant,
        200,
        150,
        1000){}


void MillennialTreeCookie::levelUp() {
    level+=1;
    damage+=150;
    defense+=150;
    health+=150;
    currHealth=health;
}

int  MillennialTreeCookie::attack(Element enemyType) {

    if (isCriticalHit()) {
        return (1 + critDamage + (1.0 * currHealth) / health + elementalAttack(enemyType)) * damage + 25;
    }
    return (1 + (1.0 * currHealth) / health + elementalAttack(enemyType)) * damage + 25;
}
bool MillennialTreeCookie::onHit(int incomingDamage) {

    int check=incomingDamage - defense * (1 + (1.0 * currHealth / health));
    defenseBuff();
    if (isDodged()||check<=0) {
        return true;
    }
    currHealth-=check;
    return false;
}