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
    int maxCritCount;
    int maxDodgeCount;
    int critCount;
    int dodgeCount;

public:
    Character(std::string name, int damage, int defense, int health, int maxCritCount, int maxDodgeCount);
    virtual ~Character() = default;
    virtual void levelUp() = 0;
    virtual bool onHit(int incomingDamage) = 0;

    bool isCriticalHit();
    bool isDodged();

    std::string getName() const;
    int getLevel() const;
    int getDamage() const;
    int getDefense() const;
    int getHealth() const;
    int getCurrHealth() const;
    int getMaxCritCount() const;
    int getMaxDodgeCount() const;
};

#endif
