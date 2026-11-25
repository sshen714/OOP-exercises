#ifndef SELTZERCOOKIE_HPP
#define SELTZERCOOKIE_HPP

#include "BackGingerbreadMan.hpp"

class SeltzerCookie final : public BackGingerbreadMan {
public:
    // SeltzerCookie();

   SeltzerCookie(
        std::string name = "Seltzer Cookie",
        Element type = Element::Water,
        int damage=100,
        int defense=400,
        int health=700,
        float critDamage = 0.8,
        int critTime = 2,
        int avoidTime = 3
    );

    void levelUp() override;
    int attack(Element enemyType) override;
    bool attacked(int incomingDamage) override;

};

#endif
