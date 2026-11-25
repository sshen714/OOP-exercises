#ifndef GINGERBREADGROUP_HPP
#define GINGERBREADGROUP_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include "GingerbreadMan.hpp"

class GingerbreadGroup {
private:
    std::vector<std::shared_ptr<GingerbreadMan>> queue;
    int maxSize;
    int currIndex;

public:
    GingerbreadGroup(int maxSize);
    std::vector<int> attack(std::vector<Element> &types);
    void onHit(std::vector<int> &damages);

    void addGingerbreadMan(std::shared_ptr<GingerbreadMan> gingerbreadMan);
    void replaceGingerbreadMan(int index, std::shared_ptr<GingerbreadMan> gingerbreadMan);

    void sortByHealth();
    void sortByDamage();
    void sortByDefense();

    int countCombatPower();
    void removeDeadGingerbreadMan();
    void removeGingerbreadMan(std::string name);
    void removeGingerbreadMan(Element element);
    std::shared_ptr<GingerbreadMan> getGingerbreadMan(int index);
};

#endif
