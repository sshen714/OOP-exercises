#include "GingerbreadGroup.hpp"
#include "BurningSpiceCookie.hpp"
#include "FireSpiritCookie.hpp"
#include "MillennialTreeCookie.hpp"
#include "SilverbellCookie.hpp"
#include "WhiteLilyCookie.hpp"

#include <gtest/gtest.h>

#include <stdexcept>
#include <vector>

TEST(GingerbreadGroupTest, Constructor) {
    EXPECT_THROW(GingerbreadGroup(2), std::invalid_argument);
    EXPECT_NO_THROW(GingerbreadGroup(3));
    EXPECT_NO_THROW(GingerbreadGroup(9));
    EXPECT_THROW(GingerbreadGroup(10), std::invalid_argument);
}

TEST(GingerbreadGroupTest, AttackWithNoCriticalCookie) {
    GingerbreadGroup group(3);
    GingerbreadMan attacker("Attacker", Element::Fire, Position::Front, 100, 0, 100, 0.5, 3, 5);
    group.addGingerbreadMan(attacker);
    std::vector<Element> enemyTypes{Element::Fire, Element::Water};

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{100, 100}));
}

TEST(GingerbreadGroupTest, AttackWithSomeCriticalCookie) {
    GingerbreadGroup group(3);
    GingerbreadMan attacker("Attacker", Element::Fire, Position::Front, 100, 0, 100, 0.5, 1, 5);
    group.addGingerbreadMan(attacker);
    std::vector<Element> enemyTypes{Element::Fire, Element::Water, Element::Plant};

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{150, 0, 0}));
}

TEST(GingerbreadGroupTest, AttackedWithNoAvoidCookie) {
    GingerbreadGroup group(3);
    GingerbreadMan member("Member", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(member);
    std::vector<float> damages{30};

    group.attacked(damages);
    EXPECT_EQ(group.getGingerbreadMan(0).getCurrHealth(), 80);
}

TEST(GingerbreadGroupTest, AttackedWithSomeAvoidCookie) {
    GingerbreadGroup group(3);
    GingerbreadMan member("Member", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 2);
    group.addGingerbreadMan(member);
    std::vector<float> damages{30};

    group.attacked(damages);
    EXPECT_EQ(group.getGingerbreadMan(0).getCurrHealth(), 80);
    group.attacked(damages);
    EXPECT_EQ(group.getGingerbreadMan(0).getCurrHealth(), 80);
}

TEST(GingerbreadGroupTest, AddGingerbreadManRejectsDuplicateNames) {
    GingerbreadGroup group(3);
    GingerbreadMan first("Same", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan duplicate("Same", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(first);

    EXPECT_THROW(group.addGingerbreadMan(duplicate), std::invalid_argument);
    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Same");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, AddGingerbreadManRejectsFullPositions) {
    GingerbreadGroup group(3);
    GingerbreadMan first("First", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan second("Second", Element::Water, Position::Front, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(first);

    EXPECT_THROW(group.addGingerbreadMan(second), std::invalid_argument);
    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "First");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, AddGingerbreadMan) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan middle("Middle", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan back("Back", Element::Plant, Position::Back, 100, 10, 100, 0.5, 3, 5);

    group.addGingerbreadMan(front);
    group.addGingerbreadMan(middle);
    group.addGingerbreadMan(back);

    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Front");
    EXPECT_EQ(group.getGingerbreadMan(1).getName(), "Middle");
    EXPECT_EQ(group.getGingerbreadMan(2).getName(), "Back");
}

TEST(GingerbreadGroupTest, ReplaceGingerbreadManRejectsDuplicateNames) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan middle("Middle", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan duplicate("Middle", Element::Plant, Position::Front, 200, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(front);
    group.addGingerbreadMan(middle);

    EXPECT_THROW(group.replaceGingerbreadMan(0, duplicate), std::invalid_argument);
    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Front");
}

TEST(GingerbreadGroupTest, ReplaceGingerbreadManRejectsInvalidIndex) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(front);

    EXPECT_THROW(group.replaceGingerbreadMan(-1, front), std::out_of_range);
    EXPECT_THROW(group.replaceGingerbreadMan(1, front), std::out_of_range);
    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Front");
}

TEST(GingerbreadGroupTest, ReplaceGingerbreadManRejectsWrongPositionCookies) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan middle("Middle", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(front);

    EXPECT_THROW(group.replaceGingerbreadMan(0, middle), std::invalid_argument);
    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Front");
}

TEST(GingerbreadGroupTest, ReplaceGingerbreadMan) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan replacement("Replacement", Element::Plant, Position::Front, 200, 20, 200, 0.5, 3, 5);
    group.addGingerbreadMan(front);

    group.replaceGingerbreadMan(0, replacement);

    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Replacement");
    EXPECT_EQ(group.getGingerbreadMan(0).getElementType(), Element::Plant);
    EXPECT_EQ(group.getGingerbreadMan(0).getDamage(), 200);
    EXPECT_EQ(group.getGingerbreadMan(0).getDefense(), 20);
    EXPECT_EQ(group.getGingerbreadMan(0).getHealth(), 200);
}

TEST(GingerbreadGroupTest, SortByHealth) {
    GingerbreadGroup group(3);
    MillennialTreeCookie front;
    WhiteLilyCookie middle;
    SilverbellCookie back;
    group.addGingerbreadMan(front);
    group.addGingerbreadMan(middle);
    group.addGingerbreadMan(back);

    group.sortByHealth();

    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "White Lily Cookie");
    EXPECT_EQ(group.getGingerbreadMan(1).getName(), "Millennial Tree Cookie");
    EXPECT_EQ(group.getGingerbreadMan(2).getName(), "Silverbell Cookie");
}

TEST(GingerbreadGroupTest, SortByDamage) {
    GingerbreadGroup group(3);
    MillennialTreeCookie front;
    WhiteLilyCookie middle;
    SilverbellCookie back;
    group.addGingerbreadMan(front);
    group.addGingerbreadMan(middle);
    group.addGingerbreadMan(back);

    group.sortByDamage();

    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Millennial Tree Cookie");
    EXPECT_EQ(group.getGingerbreadMan(1).getName(), "Silverbell Cookie");
    EXPECT_EQ(group.getGingerbreadMan(2).getName(), "White Lily Cookie");
}

TEST(GingerbreadGroupTest, SortByDefense) {
    GingerbreadGroup group(3);
    MillennialTreeCookie front;
    WhiteLilyCookie middle;
    SilverbellCookie back;
    group.addGingerbreadMan(front);
    group.addGingerbreadMan(middle);
    group.addGingerbreadMan(back);

    group.sortByDefense();

    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Silverbell Cookie");
    EXPECT_EQ(group.getGingerbreadMan(1).getName(), "Millennial Tree Cookie");
    EXPECT_EQ(group.getGingerbreadMan(2).getName(), "White Lily Cookie");
}

TEST(GingerbreadGroupTest, CountCombatPower) {
    GingerbreadGroup group(3);
    MillennialTreeCookie tree;
    WhiteLilyCookie lily;
    group.addGingerbreadMan(tree);
    group.addGingerbreadMan(lily);

    EXPECT_EQ(group.countCombatPower(), 3000);
}

TEST(GingerbreadGroupTest, RemoveDeadGingerbreadManKeepsLivingMembers) {
    GingerbreadGroup group(3);
    GingerbreadMan living("Living", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan dead("Dead", Element::Water, Position::Middle, 100, 0, 50, 0.5, 3, 100);
    EXPECT_FALSE(dead.attacked(100));
    EXPECT_LE(dead.getCurrHealth(), 0);
    group.addGingerbreadMan(living);
    group.addGingerbreadMan(dead);

    group.removeDeadGingerbreadMan();

    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Living");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, RemoveGingerbreadManByName) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan middle("Middle", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(front);
    group.addGingerbreadMan(middle);

    group.removeGingerbreadMan("Front");

    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Middle");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, RemoveGingerbreadManByElement) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Plant, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan middle("Middle", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan back("Back", Element::Plant, Position::Back, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(front);
    group.addGingerbreadMan(middle);
    group.addGingerbreadMan(back);

    group.removeGingerbreadMan(Element::Plant);

    EXPECT_EQ(group.getGingerbreadMan(0).getName(), "Middle");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, GetGingerbreadManRejectInvalidIndex) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(front);

    EXPECT_THROW(group.getGingerbreadMan(-1), std::out_of_range);
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, GetGingerbreadMan) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(front);

    GingerbreadMan actual = group.getGingerbreadMan(0);
    EXPECT_EQ(actual.getName(), "Front");
    EXPECT_EQ(actual.getElementType(), Element::Fire);
    EXPECT_EQ(actual.getPosition(), Position::Front);
    EXPECT_EQ(actual.getDamage(), 100);
    EXPECT_EQ(actual.getDefense(), 10);
    EXPECT_EQ(actual.getHealth(), 100);
}