#include "SeltzerCookie.hpp"

SeltzerCookie::SeltzerCookie(
    std::string name,
    Element type,
    int damage,
    int defense,
    int health
    ):BackGingerbreadMan(name,
        type,
        damage,
        defense,
        health,
        0.7,
        2,
        3){}

bool SeltzerCookie::onHit(int incomingDamage) {

    int check=-1+incomingDamage - defense * (1 + level / 100.0);
    keepHealingBuff();
    if (isDodged()||check<=0) {
        return true;
    }
    currHealth-=check;
    return false;
}