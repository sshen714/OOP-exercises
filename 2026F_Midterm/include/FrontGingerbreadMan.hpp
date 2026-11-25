#ifndef FRONTGINGERBREADMAN_HPP
#define FRONTGINGERBREADMAN_HPP

#include "GingerbreadMan.hpp"

class FrontGingerbreadMan : public GingerbreadMan {
public:
    FrontGingerbreadMan(
        std::string name,
        Element type,
        int damage,
        int defense,
        int health,
        float critDamage = 0.5,
        int critTime = 3,
        int avoidTime = 5
        ): GingerbreadMan(
            name, type, Position::Front,
            damage, defense, health,
            critDamage, critTime, avoidTime
        ) {}


    void defenseBuff() {

        if (defense > damage) {
            defense += 50;
        }
    }

};

#endif

