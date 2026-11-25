#ifndef CRIMSONCORALCOOKIE_HPP
#define CRIMSONCORALCOOKIE_HPP

#include "FrontGingerbreadMan.hpp"

class CrimsonCoralCookie final : public FrontGingerbreadMan {
public:
    CrimsonCoralCookie(
    std::string name="Crimson Coral Cookie",
    Element type = Element::Water,
    int damage =250,
    int defense =500,
    int health =100
    // float critDamage = 0.5,
    // int maxCritCount = 5,
    // int maxDodgeCount = 10
    );

    virtual int attack(Element enemyType) override;
};

#endif
