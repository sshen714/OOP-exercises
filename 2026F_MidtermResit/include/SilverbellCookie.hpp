#ifndef SILVERBELLCOOKIE_HPP
#define SILVERBELLCOOKIE_HPP

#include "BackGingerbreadMan.hpp"

class SilverbellCookie final : public BackGingerbreadMan {
public:
    SilverbellCookie(
    std::string name="Silverbell Cookie",
    Element type = Element::Plant,
    int damage =200,
    int defense =150,
    int health =900,
    float critDamage = 0.8,
    int maxCritCount = 3,
    int maxDodgeCount = 8
    );

    virtual void levelUp() override;
    virtual bool onHit(int incomingDamage) override;
};

#endif
