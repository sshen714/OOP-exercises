#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

class Character {
protected:
    std::string name;
    int level;
    int damage;
    int defense;
    int health;
    int currHealth;
    int critTime;
    int avoidTime;
    int currCritTime;
    int currAvoidTime;

public:
    Character(std::string name, int damage, int defense, int health, int critTime, int avoidTime);
    virtual void levelUp() = 0;
    virtual bool attacked(int incomingDamage) = 0;

    bool countCritTime();
    bool countAvoidTime();

    std::string getName() const;
    int getlevel() const;
    int getDamage() const;
    int getDefense() const;
    int getHealth() const;
    int getCurrHealth() const;
    int getCritTime() const;
    int getAvoidTime() const;
};

#endif
