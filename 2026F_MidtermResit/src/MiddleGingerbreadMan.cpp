#include "MiddleGingerbreadMan.hpp"

MiddleGingerbreadMan::MiddleGingerbreadMan(
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
            Position::Middle,
            damage,
            defense,
            health,
            critDamage,
            maxCritCount,
            maxDodgeCount){}


void MiddleGingerbreadMan::criticalBuff() {

    if (critDamage<1.0) {
        critDamage+=0.1;
    }
}