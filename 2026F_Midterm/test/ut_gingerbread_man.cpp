#include "GingerbreadMan.hpp"
#include "FrontGingerbreadMan.hpp"
#include "MiddleGingerbreadMan.hpp"
#include "BackGingerbreadMan.hpp"

#include <gtest/gtest.h>

TEST(GingerbreadManTest, Constructor){
    GingerbreadMan cookie("Test", Element::Plant, Position::Front, 100, 20, 200, 0.5, 3, 5);

    EXPECT_EQ(cookie.getName(), "Test");
    EXPECT_EQ(cookie.getlevel(), 1);
    EXPECT_EQ(cookie.getElementType(), Element::Plant);
    EXPECT_EQ(cookie.getPosition(), Position::Front);
    EXPECT_EQ(cookie.getDamage(), 100);
    EXPECT_EQ(cookie.getDefense(), 20);
    EXPECT_EQ(cookie.getHealth(), 200);
    EXPECT_EQ(cookie.getCurrHealth(), 200);
    EXPECT_EQ(cookie.getCritTime(), 3);
    EXPECT_EQ(cookie.getAvoidTime(), 5);
}

TEST(GingerbreadManTest, LevelUp){
    GingerbreadMan cookie("Test", Element::Plant, Position::Front, 100, 20, 200, 0.5, 3, 5);
    EXPECT_FALSE(cookie.attacked(50));

    cookie.levelUp();

    EXPECT_EQ(cookie.getlevel(), 2);
    EXPECT_EQ(cookie.getDamage(), 200);
    EXPECT_EQ(cookie.getDefense(), 120);
    EXPECT_EQ(cookie.getHealth(), 300);
    EXPECT_EQ(cookie.getCurrHealth(), 300);
}

TEST(GingerbreadManTest, AttackWithoutTypeEffectiveness){
    GingerbreadMan cookie("Test", Element::Fire, Position::Front, 100, 10, 200, 0.5, 3, 5);
    EXPECT_EQ(cookie.attack(Element::Fire), 100);
}

TEST(GingerbreadManTest, AttackWithTypeEffectiveness){
    GingerbreadMan plant("Plant", Element::Plant, Position::Front, 100, 0, 100, 0.5, 3, 5);
    GingerbreadMan fire("Fire", Element::Fire, Position::Front, 100, 0, 100, 0.5, 3, 5);
    GingerbreadMan water("Water", Element::Water, Position::Front, 100, 0, 100, 0.5, 3, 5);

    EXPECT_EQ(plant.attack(Element::Water), 130);
    EXPECT_EQ(fire.attack(Element::Plant), 170);
    EXPECT_EQ(water.attack(Element::Fire), 150);
}

TEST(GingerbreadManTest, CriticalAttackWithoutTypeEffectiveness){
    GingerbreadMan cookie("Test", Element::Fire, Position::Front, 100, 0, 100, 0.5, 2, 5);
    EXPECT_EQ(cookie.attack(Element::Fire), 100);
    EXPECT_EQ(cookie.attack(Element::Fire), 150);
}

TEST(GingerbreadManTest, CriticalAttackWithTypeEffectiveness){
    GingerbreadMan cookie("Test", Element::Water, Position::Front, 100, 0, 100, 0.5, 2, 5);
    EXPECT_EQ(cookie.attack(Element::Fire), 150);
    EXPECT_EQ(cookie.attack(Element::Fire), 200);
}

TEST(GingerbreadManTest, Attacked){
    GingerbreadMan cookie("Test", Element::Fire, Position::Front, 100, 20, 200, 0.5, 3, 5);
    EXPECT_FALSE(cookie.attacked(50));
    EXPECT_EQ(cookie.getCurrHealth(), 170);

    EXPECT_TRUE(cookie.attacked(10));
    EXPECT_EQ(cookie.getCurrHealth(), 170);
}

TEST(GingerbreadManTest, AvoidAttack){
    GingerbreadMan cookie("Test", Element::Fire, Position::Front, 100, 10, 200, 0.5, 3, 2);
    EXPECT_FALSE(cookie.attacked(30));
    EXPECT_EQ(cookie.getCurrHealth(), 180);
    EXPECT_TRUE(cookie.attacked(30));
    EXPECT_EQ(cookie.getCurrHealth(), 180);
}

TEST(GingerbreadManTest, GetBaseFrontInteractPositions){
    GingerbreadMan cookie("Test", Element::Fire, Position::Front, 100, 10, 200, 0.5, 3, 5);
    EXPECT_EQ(cookie.getInteractPositions(), (std::vector<Position>{Position::Front}));
}

TEST(GingerbreadManTest, ElementalAttack){
    GingerbreadMan plant("Plant", Element::Plant, Position::Front, 100, 0, 100, 0.5, 3, 5);
    GingerbreadMan fire("Fire", Element::Fire, Position::Front, 100, 0, 100, 0.5, 3, 5);
    GingerbreadMan water("Water", Element::Water, Position::Front, 100, 0, 100, 0.5, 3, 5);

    EXPECT_EQ(plant.attack(Element::Water), 130);
    EXPECT_EQ(fire.attack(Element::Water), 100);
    EXPECT_EQ(water.attack(Element::Plant), 100);
}

TEST(GingerbreadManTest, GetFrontGingerbreadInteractPositions){
    FrontGingerbreadMan cookie("Front", Element::Fire, 100, 10, 200);
    EXPECT_EQ(cookie.getPosition(), Position::Front);
    EXPECT_EQ(cookie.getInteractPositions(), (std::vector<Position>{Position::Front}));
}

TEST(GingerbreadManTest, GetMiddleGingerbreadInteractPositions){
    MiddleGingerbreadMan cookie("Middle", Element::Water, 100, 10, 200);
    EXPECT_EQ(cookie.getPosition(), Position::Middle);
    EXPECT_EQ(
        cookie.getInteractPositions(),
        (std::vector<Position>{Position::Front, Position::Middle})
    );
}

TEST(GingerbreadManTest, GetBackGingerbreadInteractPositions){
    BackGingerbreadMan cookie("Back", Element::Plant, 100, 10, 200);
    EXPECT_EQ(cookie.getPosition(), Position::Back);
    EXPECT_EQ(
        cookie.getInteractPositions(),
        (std::vector<Position>{Position::Middle, Position::Back})
    );
}

TEST(GingerbreadManTest, FrontGingerbreadManConstructor){
    FrontGingerbreadMan cookie("Front", Element::Fire, 100, 200, 300, 0.4, 4, 6);
    EXPECT_EQ(cookie.getName(), "Front");
    EXPECT_EQ(cookie.getElementType(), Element::Fire);
    EXPECT_EQ(cookie.getPosition(), Position::Front);
    EXPECT_EQ(cookie.getDamage(), 100);
    EXPECT_EQ(cookie.getDefense(), 200);
    EXPECT_EQ(cookie.getHealth(), 300);
    EXPECT_EQ(cookie.getCurrHealth(), 300);
    EXPECT_EQ(cookie.getCritTime(), 4);
    EXPECT_EQ(cookie.getAvoidTime(), 6);
}

TEST(GingerbreadManTest, FrontGingerbreadManDefenseBuffTriggersWhenDefenseIsHigher){
    FrontGingerbreadMan cookie("Front", Element::Fire, 100, 120, 200);
    cookie.defenseBuff();
    EXPECT_EQ(cookie.getDefense(), 170);
}

TEST(GingerbreadManTest, FrontGingerbreadManDefenseBuffDoesNotTriggerWhenDefenseIsNotHigher){
    FrontGingerbreadMan cookie("Front", Element::Fire, 100, 100, 200);
    cookie.defenseBuff();
    EXPECT_EQ(cookie.getDefense(), 100);
}

TEST(GingerbreadManTest, MiddleGingerbreadManCriticalBuffRaisesCriticalDamage){
    MiddleGingerbreadMan cookie("Middle", Element::Fire, 100, 0, 200, 0.2, 1);
    EXPECT_EQ(cookie.attack(Element::Fire), 120);
    cookie.criticalBuff();
    EXPECT_EQ(cookie.attack(Element::Fire), 150);
}

TEST(GingerbreadManTest, MiddleGingerbreadManCriticalBuffPreservesHigherCriticalDamage){
    MiddleGingerbreadMan cookie("Middle", Element::Fire, 100, 0, 200, 0.8, 1);
    cookie.criticalBuff();
    EXPECT_EQ(cookie.attack(Element::Fire), 180);
}

TEST(GingerbreadManTest, BackGingerbreadManHealingBuffRestoresOneHealth){
    BackGingerbreadMan cookie("Back", Element::Plant, 100, 0, 200, 0.5, 3, 5);
    EXPECT_FALSE(cookie.attacked(20));
    EXPECT_EQ(cookie.getCurrHealth(), 180);
    cookie.keepHealingBuff();
    EXPECT_EQ(cookie.getCurrHealth(), 181);
}

TEST(GingerbreadManTest, BackGingerbreadManHealingBuffDoesNotTriggerAtFullHealth){
    BackGingerbreadMan cookie("Back", Element::Plant, 100, 0, 200, 0.5, 3, 5);
    cookie.keepHealingBuff();
    EXPECT_EQ(cookie.getCurrHealth(), 200);
}