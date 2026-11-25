#ifndef GINGERBREADGROUP_HPP
#define GINGERBREADGROUP_HPP

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include "GingerbreadMan.hpp"

class GingerbreadGroup {
private:
    std::vector<GingerbreadMan> queue;
    int maxSize;
    int currIndex;

public:
    GingerbreadGroup(int maxSize);
    std::vector<int> attack(std::vector<Element> &types);
    void attacked(std::vector<float> &damages);

    void addGingerbreadMan(const GingerbreadMan &gingerbreadMan);
    void replaceGingerbreadMan(int index, const GingerbreadMan &gingerbreadMan);

    void sortByHealth();
    void sortByDamage();
    void sortByDefense();

    int countCombatPower();
    void removeDeadGingerbreadMan();
    void removeGingerbreadMan(std::string name);
    void removeGingerbreadMan(Element element);
    GingerbreadMan getGingerbreadMan(int index);
};

#endif
