#include "Character.hpp"

Character::Character(std::string name, int damage, int defense, int health, int critTime, int avoidTime) {

    this->name=name;
    level=1;
    this->damage=damage;
    this->defense=defense;
    this->health=health;
    this->critTime=critTime;
    this->avoidTime=avoidTime;
    currHealth=health;
    currCritTime=0;
    currAvoidTime=0;
}


bool Character::countCritTime() {
    currCritTime+=1;
    if (currCritTime==critTime) {
        currCritTime=0;
        return true;
    }
    return false;
}

bool Character::countAvoidTime() {
    currAvoidTime+=1;
    if (currAvoidTime == avoidTime) {
        currAvoidTime=0;
        return true;
    }
    return false;
}

std::string Character::getName() const { return name;}

int Character::getlevel() const{ return level;}
int Character::getDamage() const{  return damage;}
int Character::getDefense() const{ return defense;}
int Character::getHealth() const{ return  health;}
int Character::getCurrHealth() const{ return currHealth;}
int Character::getCritTime() const{ return critTime;}
int Character::getAvoidTime() const{ return avoidTime;}