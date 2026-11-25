#ifndef GINGERBREADMAN_HPP
#define GINGERBREADMAN_HPP

#include <string>
#include <vector>
#include "Character.hpp"

enum class Position { Front, Middle, Back };

enum class Element { Fire, Water, Plant };

class GingerbreadMan : public Character {
private:
    Element type;
    Position pos;

public:
    GingerbreadMan(
        std::string name,
        Element type,
        Position pos,
        int damage,
        int defense,
        int health,
        float critDamage,
        int maxCritCount,
        int maxDodgeCount
    );

    virtual void levelUp() override;
    virtual int attack(Element enemyType);
    virtual bool onHit(int incomingDamage) override;
    std::vector<Position> getInteractPositions() const;
    
    Element getElementType() const;
    Position getPosition() const;
    float getCritDamage() const;

protected:
    float critDamage;
    float elementalAttack(Element enemyType);
};

#endif
