#ifndef MIDDLEGINGERBREADMAN_HPP
#define MIDDLEGINGERBREADMAN_HPP

#include "GingerbreadMan.hpp"

class MiddleGingerbreadMan : public GingerbreadMan {
public:
    MiddleGingerbreadMan(
        std::string name,
        Element type,
        int damage,
        int defense,
        int health,
        float critDamage = 0.5,
        int critTime = 3,
        int avoidTime = 5
        ): GingerbreadMan(
                name, type, Position::Middle,
                damage, defense, health,
                critDamage, critTime, avoidTime
            ){}

    void criticalBuff() {

        if (getCritDamage() < 0.5) {
            critDamage=0.5;
        }
    }

};

#endif

