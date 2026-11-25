#include "BurningSpiceCookie.hpp"

BurningSpiceCookie::BurningSpiceCookie(
    std::string name,
    Element type,
    int damage,
    int defense,
    int health
        ):FrontGingerbreadMan(
         name,
            type,
            damage,
            defense,
            health,
            0.5,
            3,
            5
            ){}

void BurningSpiceCookie::levelUp() {
    level+=1;
    damage+=250;
    critDamage+=0.05;
    health+=220;
    currHealth=health;
}
int BurningSpiceCookie::attack(Element enemyType) {
    if (isCriticalHit()) {
        return (1 + critDamage + elementalAttack(enemyType)) * (damage + 25);
    }
    return (1 + elementalAttack(enemyType)) * (damage + 25);
}