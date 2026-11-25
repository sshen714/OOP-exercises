#ifndef SILVERBELLCOOKIE_HPP
#define SILVERBELLCOOKIE_HPP

#include "BackGingerbreadMan.hpp"

class SilverbellCookie final : public BackGingerbreadMan {
public:
    // SilverbellCookie();

    SilverbellCookie(
        std::string name = "Silverbell Cookie",
        Element type = Element::Plant,
        int damage=200,
        int defense=150,
        int health=900,
        float critDamage = 0.8,
        int critTime = 3,
        int avoidTime = 8
    );

    void levelUp() override;
    int attack(Element enemyType) override;
    bool attacked(int incomingDamage) override;

};

#endif
