#ifndef CRIMSONCORALCOOKIE_HPP
#define CRIMSONCORALCOOKIE_HPP

#include "FrontGingerbreadMan.hpp"

class CrimsonCoralCookie final : public FrontGingerbreadMan {
public:
    // CrimsonCoralCookie();

    CrimsonCoralCookie(
    std::string name = "Crimson Coral Cookie",
    Element type = Element::Water,
    int damage=200,
    int defense=500,
    int health=100,
    float critDamage = 0.5,
    int critTime = 3,
    int avoidTime = 10
    );

    void levelUp() override;
    int attack(Element enemyType) override;
    bool attacked(int incomingDamage) override;

};


#endif
