#ifndef MILLENNIALTREECOOKIE_HPP
#define MILLENNIALTREECOOKIE_HPP

#include "FrontGingerbreadMan.hpp"

class MillennialTreeCookie final : public FrontGingerbreadMan {
public:
    MillennialTreeCookie(
        std::string name = "Millennial Tree Cookie",
        Element type = Element::Plant,
        int damage =200,
        int defense =100,
        int health =1000 ,
        float critDamage =0.5,
        int critTime=3,
        int avoidTime=5
    );



    void levelUp() override;
    int attack(Element enemyType) override;
    bool attacked(int incomingDamage) override;


};

#endif
