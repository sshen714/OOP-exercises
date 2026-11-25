#ifndef CHILIPEPPERCOOKIE_HPP
#define CHILIPEPPERCOOKIE_HPP

#include "MiddleGingerbreadMan.hpp"

class ChiliPepperCookie final : public MiddleGingerbreadMan {
public:
    // ChiliPepperCookie();

    ChiliPepperCookie(
    std::string name = "Chili Pepper Cookie",
    Element type = Element::Fire,
    int damage=200,
    int defense=100,
    int health=700,
    float critDamage = 0.8,
    int critTime = 7,
    int avoidTime = 3
    );

    void levelUp() override;
    int attack(Element enemyType) override;
    bool attacked(int incomingDamage) override;

};


#endif
