#include "GingerbreadMan.hpp"

GingerbreadMan::GingerbreadMan(
        std::string name,
        Element type,
        Position pos,
        int damage,
        int defense,
        int health,
        float critDamage,
        int critTime,
        int avoidTime
    ) : Character(name,damage,defense,health,critTime,avoidTime),
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
    float crit=0;

    if (countCritTime()){
        crit=critDamage;
    }

    return (1 + crit + elementalAttack(enemyType)) * damage;
}

float GingerbreadMan::elementalAttack(Element enemyType) {

    if (type==Element::Water && enemyType==Element:: Fire ) { return 0.5; }
    if (type==Element::Fire && enemyType==Element:: Plant ) { return 0.7; }
    if (type==Element::Plant && enemyType==Element:: Water ) { return 0.3; }
    return 0;
}

bool GingerbreadMan::attacked(int incomingDamage) {

    int realDamage = incomingDamage - defense;
    if (countAvoidTime() || realDamage <= 0) {
        return true;
    }
    currHealth -=realDamage;
    return false;

}

std::vector<Position> GingerbreadMan::getInteractPositions() const {

    std::vector<Position> a;
    if (pos == Position::Front) {
        a.push_back(Position::Front);
    }

    if (pos == Position::Middle) {
        a.push_back(Position::Front);
        a.push_back(Position::Middle);
    }

    if (pos == Position::Back) {
        a.push_back(Position::Middle);
        a.push_back(Position::Back);
    }

    return a;
}

Element GingerbreadMan::getElementType() const{ return type; }
Position GingerbreadMan::getPosition() const{ return pos; }
float GingerbreadMan::getCritDamage() const{ return critDamage; }