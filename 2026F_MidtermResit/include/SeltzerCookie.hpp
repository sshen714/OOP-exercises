#ifndef SELTZERCOOKIE_HPP
#define SELTZERCOOKIE_HPP

#include "BackGingerbreadMan.hpp"

class SeltzerCookie final : public BackGingerbreadMan {
public:
    SeltzerCookie(
    std::string name="Seltzer Cookie",
    Element type = Element::Water,
    int damage =200,
    int defense =450,
    int health =700
    );

    virtual bool onHit(int incomingDamage) override;
};

#endif
