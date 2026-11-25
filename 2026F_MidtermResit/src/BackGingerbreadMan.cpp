#include "BackGingerbreadMan.hpp"

BackGingerbreadMan::BackGingerbreadMan(
        std::string name,
        Element type,
        int damage,
        int defense,
        int health,
        float critDamage,
        int maxCritCount,
        int maxDodgeCount
        ):GingerbreadMan(name,
            type,
            Position::Back,
            damage,
            defense,
            health,
            critDamage,
            maxCritCount,
            maxDodgeCount){}

void BackGingerbreadMan::keepHealingBuff() {

    if (health>currHealth) {
        currHealth+=1;
    }
}