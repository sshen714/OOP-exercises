#ifndef FIRESPIRITCOOKIE_HPP
#define FIRESPIRITCOOKIE_HPP

#include "BackGingerbreadMan.hpp"

class FireSpiritCookie final : public BackGingerbreadMan {
public:
    // FireSpiritCookie();
    FireSpiritCookie(
   std::string name = "Fire Spirit Cookie",
   Element type = Element::Fire,
   int damage=500,
   int defense=40,
   int health=200,
   float critDamage = 0.5,
   int critTime = 2,
   int avoidTime = 7
   );

    void levelUp() override;
    int attack(Element enemyType) override;
    bool attacked(int incomingDamage) override;
};

#endif
