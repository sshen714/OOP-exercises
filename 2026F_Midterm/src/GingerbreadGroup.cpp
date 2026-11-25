#include "GingerbreadGroup.hpp"


GingerbreadGroup::GingerbreadGroup(int maxSize) {

    if (maxSize<3 || maxSize>9) {
        throw std::invalid_argument("");
    }
    this->maxSize=maxSize;
    currIndex=0;

}

std::vector<int> GingerbreadGroup::attack(std::vector<Element> &types) {

    std::vector<int> hurt(types.size(), 0);
    if (queue.empty()) {
        return hurt;
    }

    GingerbreadMan& attacker = queue[currIndex];
    std::vector<Position> allowed = attacker.getInteractPositions();
    int unit = types.size() / 3;

    for (int i = 0; i < types.size(); ++i) {
        if (types.size() < 3) {
            hurt[i] = attacker.attack(types[i]);
            continue;
        }

        Position enemyPosition;
        if (i < unit)
            enemyPosition = Position::Front;
        else if (i < 2 * unit)
            enemyPosition = Position::Middle;
        else
            enemyPosition = Position::Back;

        for (Position position : allowed) {
            if (position == enemyPosition) {
                hurt[i] = attacker.attack(types[i]);
                break;
            }
        }
    }

    currIndex = currIndex + 1;
    return hurt;

}

void GingerbreadGroup::attacked(std::vector<float> &damages) {

    if (damages.size() != queue.size()) {
        throw std::invalid_argument("");
    }

    for (int i=0; i<queue.size(); i++) {
        queue[i].attacked(damages[i]);
        removeDeadGingerbreadMan();
    }

}

void GingerbreadGroup::addGingerbreadMan(const GingerbreadMan &gingerbreadMan) {

    int samePositionCount = 0;
    Position newPosition = gingerbreadMan.getPosition();

    for (const GingerbreadMan& existing : queue) {
        if (existing.getName() == gingerbreadMan.getName()) {
            throw std::invalid_argument("");
        }

        if (existing.getPosition() == newPosition) {
            samePositionCount++;
        }
    }

    int positionCapacity;
    if (newPosition == Position::Back) {
        positionCapacity = maxSize - 2 * (maxSize / 3);
    } else {
        positionCapacity = maxSize / 3;
    }

    if (samePositionCount >= positionCapacity) {
        throw std::invalid_argument("");
    }

    queue.push_back(gingerbreadMan);

}

void GingerbreadGroup::replaceGingerbreadMan(int index, const GingerbreadMan &gingerbreadMan) {

    if (index<0 || index >= queue.size()){ throw std::out_of_range(""); }
    for (const GingerbreadMan &checkgingerbreadMan :queue) {
        if (checkgingerbreadMan.getName()==gingerbreadMan.getName()) {
            throw std::invalid_argument("");
        }
    }

    if (queue[index].getPosition()!=gingerbreadMan.getPosition()) {
        throw std::invalid_argument("");
    }
    queue[index]=gingerbreadMan;
}

void GingerbreadGroup::sortByHealth() {

    std::sort(queue.begin(),queue.end(),[](const auto& a, const auto& b) {
        return a.getHealth() > b.getHealth();
    });

}
void GingerbreadGroup::sortByDamage() {

    std::sort(queue.begin(),queue.end(),[](const auto& a, const auto& b) {
        return a.getDamage() > b.getDamage();
    });
}
void GingerbreadGroup::sortByDefense() {

    std::sort(queue.begin(),queue.end(),[](const auto& a, const auto& b) {
        return a.getDefense() > b.getDefense();
    });
}

int GingerbreadGroup::countCombatPower() {

    int total=0;
    for (const GingerbreadMan &temp :queue) {
        total=total+temp.getDamage()+temp.getDefense()+temp.getHealth();
    }

    return total;
}
void GingerbreadGroup::removeDeadGingerbreadMan() {

    int index=0;
    for (const GingerbreadMan &temp :queue) {
        index+=1;
        if (temp.getCurrHealth()<=0) {
            queue.erase(queue.begin()+index);
        }
    }
    if (queue.empty()) {
        currIndex=0;
    }
}

void GingerbreadGroup::removeGingerbreadMan(std::string name) {

    int index=0;
    for (const GingerbreadMan &temp :queue) {
        index+=1;
        if (temp.getName()==name) {
            queue.erase(queue.begin()+index);
        }
    }

}

void GingerbreadGroup::removeGingerbreadMan(Element element) {

    int index=0;
    for (const GingerbreadMan &temp :queue) {
        index+=1;
        if (temp.getElementType()==element) {
            queue.erase(queue.begin()+index);
        }
    }
}

GingerbreadMan GingerbreadGroup::getGingerbreadMan(int index) {

    if (index < 0 || index >= queue.size()) {
        throw std::out_of_range("");
    }

    return queue[index];
}