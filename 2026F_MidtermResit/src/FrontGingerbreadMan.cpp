#include "FrontGingerbreadMan.hpp"

FrontGingerbreadMan::FrontGingerbreadMan(
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
            Position::Front,
            damage,
            defense,
            health,
            critDamage,
            maxCritCount,
            maxDodgeCount){}


void FrontGingerbreadMan::defenseBuff() {

    if (defense>damage){ defense*=1.1; }
}