#ifndef CHILIPEPPERCOOKIE_HPP
#define CHILIPEPPERCOOKIE_HPP

#include "MiddleGingerbreadMan.hpp"

class ChiliPepperCookie final : public MiddleGingerbreadMan {
public:
    ChiliPepperCookie(
    std::string name ="Chili Pepper Cookie",
    Element type =Element::Fire,
    int damage=200,
    int defense=100,
    int health=900
    );

    virtual void levelUp() override;
    virtual int attack(Element enemyType) override;
};

#endif
