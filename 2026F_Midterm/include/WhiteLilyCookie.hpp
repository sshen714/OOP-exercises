#ifndef WHITELILYCOOKIE_HPP
#define WHITELILYCOOKIE_HPP

#include "MiddleGingerbreadMan.hpp"

class WhiteLilyCookie final : public MiddleGingerbreadMan{
public:
    WhiteLilyCookie(
    std::string name = "White Lily Cookie",
    Element type = Element::Plant,
    int damage=100,
    int defense=100,
    int health=1500,
    float critDamage = 0.2,
    int critTime = 2,
    int avoidTime = 5
    );

    void levelUp() override;
    int attack(Element enemyType) override;
    bool attacked(int incomingDamage) override;

};

#endif