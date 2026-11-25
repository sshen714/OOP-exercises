#ifndef SEAFAIRYCOOKIE_HPP
#define SEAFAIRYCOOKIE_HPP

#include "MiddleGingerbreadMan.hpp"

class SeaFairyCookie final : public MiddleGingerbreadMan {
public:
    // SeaFairyCookie();
    SeaFairyCookie(
    std::string name = "Sea Fairy Cookie",
    Element type = Element::Water,
    int damage=200,
    int defense=300,
    int health=1000,
    float critDamage = 0.3,
    int critTime = 3,
    int avoidTime = 5
    );

    void levelUp() override;
    int attack(Element enemyType) override;
    bool attacked(int incomingDamage) override;

};

#endif
