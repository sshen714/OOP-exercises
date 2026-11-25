#ifndef MILLENNIALTREECOOKIE_HPP
#define MILLENNIALTREECOOKIE_HPP

#include "FrontGingerbreadMan.hpp"

class MillennialTreeCookie final : public FrontGingerbreadMan {
public:
    MillennialTreeCookie();

    virtual void levelUp() override;
    virtual int  attack(Element enemyType) override;
    virtual bool onHit(int incomingDamage) override;
};

#endif
