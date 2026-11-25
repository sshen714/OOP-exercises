#include "GingerbreadMan.hpp"


GingerbreadMan::GingerbreadMan(
        std::string name,
        Element type,
        Position pos,
        int damage,
        int defense,
        int health,
        float critDamage,
        int maxCritCount,
        int maxDodgeCount
    ):Character(name,damage,defense,health,maxCritCount, maxDodgeCount),
    type(type),
    pos(pos),
    critDamage(critDamage){}

void GingerbreadMan::levelUp() {
    level+=1;
    damage+=100;
    defense+=100;
    health+=100;
    currHealth=health;
}

int GingerbreadMan::attack(Element enemyType) {

    if (isCriticalHit()) {
        return (1 + critDamage + elementalAttack(enemyType)) * damage;
    }
    return (1 + elementalAttack(enemyType)) * damage;

}
bool GingerbreadMan::onHit(int incomingDamage) {

    int check=incomingDamage - defense;
    if (isDodged()||check<=0) {
        return true;
    }
    currHealth-=check;
    return false;

}

std::vector<Position> GingerbreadMan::getInteractPositions() const {

    std::vector<Position> a;

    if (pos==Position::Front) {
        a.push_back(Position::Front);
    }

    if (pos==Position::Middle) {
        a.push_back(Position::Front);
        a.push_back(Position::Middle);
    }

    if (pos==Position::Back) {
        a.push_back(Position::Middle);
        a.push_back(Position::Back);
    }

    return a;
}

float GingerbreadMan::elementalAttack(Element enemyType) {

    if (type==Element::Water && enemyType==Element::Fire){ return 0.7; }
    if (type==Element::Fire && enemyType==Element::Plant){ return 1.0; }
    if (type==Element::Plant && enemyType==Element::Water){ return 0.5; }
    return 0;

}

Element GingerbreadMan::getElementType() const{ return type; }
Position GingerbreadMan::getPosition() const{ return pos; }
float GingerbreadMan::getCritDamage() const{ return critDamage;}