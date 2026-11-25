#ifndef SEAFAIRYCOOKIE_HPP
#define SEAFAIRYCOOKIE_HPP

#include "MiddleGingerbreadMan.hpp"

class SeaFairyCookie final : public MiddleGingerbreadMan {
public:
    SeaFairyCookie(
    std::string name="Sea Fairy Cookie",
    Element type = Element::Water,
    int damage =200,
    int defense =300,
    int health =1000
);
    virtual void levelUp() override;
    virtual int attack(Element enemyType) override;
};

#endif
