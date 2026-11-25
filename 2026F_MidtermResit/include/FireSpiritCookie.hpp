#ifndef FIRESPIRITCOOKIE_HPP
#define FIRESPIRITCOOKIE_HPP

#include "BackGingerbreadMan.hpp"

class FireSpiritCookie final : public BackGingerbreadMan {
public:
    FireSpiritCookie(
    std::string name="Fire Spirit Cookie",
    Element type = Element::Fire,
    int damage =500,
    int defense =20,
    int health =200,
    float critDamage = 0.5,
    int maxCritCount = 2,
    int maxDodgeCount = 7
    );

    virtual void levelUp() override;
};

#endif
