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
        int maxCritCount = 3,
        int maxDodgeCount = 5
    );    
    void criticalBuff();
};

#endif
