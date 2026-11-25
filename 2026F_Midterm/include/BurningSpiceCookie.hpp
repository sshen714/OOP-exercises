#ifndef BURNINGSPICECOOKIE_HPP
#define BURNINGSPICECOOKIE_HPP

#include "FrontGingerbreadMan.hpp"

class BurningSpiceCookie final : public FrontGingerbreadMan {
public:

    BurningSpiceCookie(
        std::string name = "Burning Spice Cookie",
        Element type = Element::Fire,
        int damage=200,
        int defense=100,
        int health=1000,
        float critDamage = 0.5,
        int critTime = 3,
        int avoidTime = 5
    );

    void levelUp() override;
    int attack(Element enemyType) override;
    bool attacked(int incomingDamage) override;
};

#endif
