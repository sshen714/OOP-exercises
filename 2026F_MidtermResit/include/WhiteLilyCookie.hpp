#ifndef WHITELILYCOOKIE_HPP
#define WHITELILYCOOKIE_HPP

#include "MiddleGingerbreadMan.hpp"

class WhiteLilyCookie final : public MiddleGingerbreadMan{
public:
    WhiteLilyCookie();

    virtual int attack(Element enemyType) override;
    virtual bool onHit(int incomingDamage) override;
};

#endif