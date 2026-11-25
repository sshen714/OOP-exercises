#include "Character.hpp"

Character::Character(std::string name, int damage, int defense, int health, int maxCritCount, int maxDodgeCount) {

    this->name=name;
    level=1;
    this->damage=damage;
    this->defense=defense;
    this->health=health;
    this->currHealth=health;
    this->maxCritCount=maxCritCount;
    this->maxDodgeCount=maxDodgeCount;
    critCount=0;
    dodgeCount=0;
}


bool Character::isCriticalHit() {

    critCount+=1;
    if (critCount==maxCritCount) {
        critCount=0;
        return true;
    }
    return false;
}

bool Character::isDodged() {

    dodgeCount+=1;
    if (dodgeCount==maxDodgeCount) {
        dodgeCount=0;
        return true;
    }
    return false;

}

std::string Character::getName() const {
    return name;
}

int Character::getLevel() const {
    return level;
}
int Character::getDamage() const {
    return damage;
}
int Character::getDefense() const{ return defense; }
int Character::getHealth() const{ return  health; }
int Character::getCurrHealth() const{ return currHealth; }
int Character::getMaxCritCount() const{ return  maxCritCount;}
int Character::getMaxDodgeCount() const{ return maxDodgeCount;}