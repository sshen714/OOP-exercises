#include "ChiliPepperCookie.hpp"

ChiliPepperCookie::ChiliPepperCookie(
        std::string name,
        Element type,
        int damage,
        int defense,
        int health
        ):MiddleGingerbreadMan(
         name,
            type,
            damage,
            defense,
            health,
            0.8,
            7,
            4
            ){}


void ChiliPepperCookie::levelUp() {

    level+=1;
    damage+=200;
    defense+=100;
    health+=100;
    currHealth=health;
    criticalBuff();

}
int ChiliPepperCookie::attack(Element enemyType) {
    if (isCriticalHit()) {
        return(1 + critDamage + (1.0 * currHealth / health) + elementalAttack(enemyType)) * damage;
    }
    return (1 + (1.0 * currHealth / health) + elementalAttack(enemyType)) * damage;
}