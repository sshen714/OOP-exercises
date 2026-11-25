#include "GingerbreadGroup.hpp"

#include <algorithm>
#include <stdexcept>


GingerbreadGroup::GingerbreadGroup(int maxSize) {

    if (maxSize<3 || maxSize>9) {
        throw std::invalid_argument("");
    }

    this->maxSize=maxSize;
    currIndex = 0;
}

std::vector<int> GingerbreadGroup::attack(std::vector<Element> &types) {

    std::vector<int> hurt(types.size(),0);

    if (queue.empty()) {
        return hurt;
    }

    if (currIndex<0 || currIndex>=queue.size()) {
        throw std::invalid_argument("");
    }

    GingerbreadMan& attacker = *queue[currIndex];
    std::vector<Position> allowed = attacker.getInteractPositions();
    int unit = types.size() / 3;

    for (int i=0 ; i<types.size(); i++) {
        if (types.size()<3) {
            hurt[i]=attacker.attack(types[i]);
            continue;
        }

        Position emPos;
        if (i < unit){ emPos=Position::Front; }
        else if (i < unit*2) { emPos=Position::Middle; }
        else { emPos=Position::Back; }

        for (Position position : allowed) {
            if (position == emPos) {
                hurt[i]=attacker.attack(types[i]);
            }
        }
    }

    currIndex=(currIndex+1)%queue.size();

    return hurt;
}

void GingerbreadGroup::onHit(std::vector<int> &damages) {

    if (damages.size() != queue.size()) {
        throw std::invalid_argument("");
    }

    for (int i=0; i<queue.size(); i++) {
        queue[i]->onHit(damages[i]);
        removeDeadGingerbreadMan();
    }

}

void GingerbreadGroup::addGingerbreadMan(std::shared_ptr<GingerbreadMan> gingerbreadMan) {

    int samePositionCount = 0;
    Position newPosition = gingerbreadMan->getPosition();

    for (const auto& existing : queue) {
        if (existing->getName() == gingerbreadMan->getName()) {
            throw std::invalid_argument("");
        }

        if (existing->getPosition() == newPosition) {
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

void GingerbreadGroup::replaceGingerbreadMan(int index, std::shared_ptr<GingerbreadMan> gingerbreadMan) {

    if (index<0 || index >= queue.size()){ throw std::out_of_range(""); }
    for (const auto& checkgingerbreadMan :queue) {
        if (checkgingerbreadMan->getName()==gingerbreadMan->getName()) {
            throw std::invalid_argument("");
        }
    }

    if (queue[index]->getPosition()!=gingerbreadMan->getPosition()) {
        throw std::invalid_argument("");
    }
    queue[index]=gingerbreadMan;
}

void GingerbreadGroup::sortByHealth() {
    std::sort(queue.begin(),queue.end(),[](const auto& a, const auto& b) {
       return a->getHealth() > b->getHealth();
   });
}
void GingerbreadGroup::sortByDamage() {
    std::sort(queue.begin(),queue.end(),[](const auto& a, const auto& b) {
       return a->getDamage() > b->getDamage();
   });
}
void GingerbreadGroup::sortByDefense() {
    std::sort(queue.begin(),queue.end(),[](const auto& a, const auto& b) {
       return a->getDefense() > b->getDefense();
   });
}

int GingerbreadGroup::countCombatPower() {
    int total=0;
    for (const auto& temp :queue) {
        total=total+temp->getDamage()+temp->getDefense()+temp->getHealth();
    }

    return total;
}
void GingerbreadGroup::removeDeadGingerbreadMan() {

    int index=0;
    for (const auto&temp :queue) {
        index+=1;
        if (temp->getCurrHealth()<=0) {
            queue.erase(queue.begin()+index);
        }
    }
    if (queue.empty()) {
        currIndex=0;
    }
}
void GingerbreadGroup::removeGingerbreadMan(std::string name) {

    int index=0;
    for (const auto& temp :queue) {
        index+=1;
        if (temp->getName()==name) {
            queue.erase(queue.begin()+index);
        }
    }
}
void GingerbreadGroup::removeGingerbreadMan(Element element) {
    int index=0;
    for (const auto& temp :queue) {
        index+=1;
        if (temp->getElementType()==element) {
            queue.erase(queue.begin()+index);
        }
    }
}
std::shared_ptr<GingerbreadMan> GingerbreadGroup::getGingerbreadMan(int index) {
    if (index < 0 || index >= queue.size()) {
        throw std::out_of_range("");
    }

    return queue[index];
}