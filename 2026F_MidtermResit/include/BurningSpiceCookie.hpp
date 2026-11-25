#ifndef BURNINGSPICECOOKIE_HPP
#define BURNINGSPICECOOKIE_HPP

#include "FrontGingerbreadMan.hpp"

class BurningSpiceCookie final : public FrontGingerbreadMan {
public:
    BurningSpiceCookie(
    std::string name="Burning Spice Cookie",
    Element type = Element::Fire,
    int damage =200,
    int defense =80,
    int health =1000
        );
    virtual void levelUp() override;
    virtual int attack(Element enemyType) override;
};

#endif
