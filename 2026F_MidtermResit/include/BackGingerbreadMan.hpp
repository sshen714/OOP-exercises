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
        int maxCritCount = 3,
        int maxDodgeCount = 5
    );
    void keepHealingBuff();
};

#endif
