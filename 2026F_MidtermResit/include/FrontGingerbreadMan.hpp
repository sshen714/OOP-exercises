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
        int maxCritCount = 3,
        int maxDodgeCount = 5
    );
    void defenseBuff();
};

#endif
