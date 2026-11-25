#ifndef BACKGINGERBREADMAN_HPP
#define BACKGINGERBREADMAN_HPP

#include "GingerbreadMan.hpp"

class BackGingerbreadMan : public GingerbreadMan {
public:
    BackGingerbreadMan(
        std::string name,
        Element type,
        int damage,
        int defense,
        int health,
        float critDamage = 0.5,
        int critTime = 3,
        int avoidTime = 5
        ): GingerbreadMan(
                name, type, Position::Back,
                damage, defense, health,
                critDamage, critTime, avoidTime
            ) {}

    void keepHealingBuff() {

        if (health > currHealth) {
            currHealth+=1;
        }
    }

};

#endif
