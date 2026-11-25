#include "FrontGingerbreadMan.hpp"
#include "MiddleGingerbreadMan.hpp"
#include "BackGingerbreadMan.hpp"

#include <gtest/gtest.h>

TEST(PositionalGingerbreadManTest, GetFrontGingerbreadInteractPositions){
    FrontGingerbreadMan cookie("Front", Element::Fire, 100, 10, 200);
    EXPECT_EQ(cookie.getPosition(), Position::Front);
    EXPECT_EQ(cookie.getInteractPositions(), (std::vector<Position>{Position::Front}));
}

TEST(PositionalGingerbreadManTest, GetMiddleGingerbreadInteractPositions){
    MiddleGingerbreadMan cookie("Middle", Element::Water, 100, 10, 200);
    EXPECT_EQ(cookie.getPosition(), Position::Middle);
    EXPECT_EQ(
        cookie.getInteractPositions(),
        (std::vector<Position>{Position::Front, Position::Middle})
    );
}

TEST(PositionalGingerbreadManTest, GetBackGingerbreadInteractPositions){
    BackGingerbreadMan cookie("Back", Element::Plant, 100, 10, 200);
    EXPECT_EQ(cookie.getPosition(), Position::Back);
    EXPECT_EQ(
        cookie.getInteractPositions(),
        (std::vector<Position>{Position::Middle, Position::Back})
    );
}

TEST(PositionalGingerbreadManTest, FrontGingerbreadManConstructor){
    FrontGingerbreadMan cookie("Front", Element::Fire, 100, 200, 300, 0.4, 4, 6);
    EXPECT_EQ(cookie.getName(), "Front");
    EXPECT_EQ(cookie.getElementType(), Element::Fire);
    EXPECT_EQ(cookie.getPosition(), Position::Front);
    EXPECT_EQ(cookie.getDamage(), 100);
    EXPECT_EQ(cookie.getDefense(), 200);
    EXPECT_EQ(cookie.getHealth(), 300);
    EXPECT_EQ(cookie.getCurrHealth(), 300);
    EXPECT_EQ(cookie.getMaxCritCount(), 4);
    EXPECT_EQ(cookie.getMaxDodgeCount(), 6);
}

TEST(PositionalGingerbreadManTest, FrontGingerbreadManDefenseBuffTriggersWhenDefenseIsHigher){
    FrontGingerbreadMan cookie("Front", Element::Fire, 100, 120, 200);
    cookie.defenseBuff();
    EXPECT_EQ(cookie.getDefense(), 132);
}

TEST(PositionalGingerbreadManTest, FrontGingerbreadManDefenseBuffDoesNotTriggerWhenDefenseIsNotHigher){
    FrontGingerbreadMan cookie("Front", Element::Fire, 100, 100, 200);
    cookie.defenseBuff();
    EXPECT_EQ(cookie.getDefense(), 100);
}

TEST(PositionalGingerbreadManTest, MiddleGingerbreadManCriticalBuffRaisesCriticalDamage){
    MiddleGingerbreadMan cookie("Middle", Element::Fire, 100, 0, 200, 0.2, 1);
    EXPECT_EQ(cookie.attack(Element::Fire), 120);
    cookie.criticalBuff();
    EXPECT_EQ(cookie.attack(Element::Fire), 130);
}

TEST(PositionalGingerbreadManTest, MiddleGingerbreadManCriticalBuffPreservesHigherCriticalDamage){
    MiddleGingerbreadMan cookie("Middle", Element::Fire, 100, 0, 200, 1.0, 1);
    cookie.criticalBuff();
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 1.0f);
    EXPECT_EQ(cookie.attack(Element::Fire), 200);
}

TEST(PositionalGingerbreadManTest, BackGingerbreadManHealingBuffRestoresOneHealth){
    BackGingerbreadMan cookie("Back", Element::Plant, 100, 0, 200, 0.5, 3, 5);
    EXPECT_FALSE(cookie.onHit(20));
    EXPECT_EQ(cookie.getCurrHealth(), 180);
    cookie.keepHealingBuff();
    EXPECT_EQ(cookie.getCurrHealth(), 181);
}

TEST(PositionalGingerbreadManTest, BackGingerbreadManHealingBuffDoesNotTriggerAtFullHealth){
    BackGingerbreadMan cookie("Back", Element::Plant, 100, 0, 200, 0.5, 3, 5);
    cookie.keepHealingBuff();
    EXPECT_EQ(cookie.getCurrHealth(), 200);
}