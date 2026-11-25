#include "GingerbreadMan.hpp"

#include <gtest/gtest.h>

TEST(GingerbreadManTest, Constructor){
    GingerbreadMan cookie("Test", Element::Plant, Position::Front, 100, 20, 200, 0.5, 3, 5);

    EXPECT_EQ(cookie.getName(), "Test");
    EXPECT_EQ(cookie.getLevel(), 1);
    EXPECT_EQ(cookie.getElementType(), Element::Plant);
    EXPECT_EQ(cookie.getPosition(), Position::Front);
    EXPECT_EQ(cookie.getDamage(), 100);
    EXPECT_EQ(cookie.getDefense(), 20);
    EXPECT_EQ(cookie.getHealth(), 200);
    EXPECT_EQ(cookie.getCurrHealth(), 200);
    EXPECT_EQ(cookie.getMaxCritCount(), 3);
    EXPECT_EQ(cookie.getMaxDodgeCount(), 5);
}

TEST(GingerbreadManTest, LevelUp){
    GingerbreadMan cookie("Test", Element::Plant, Position::Front, 100, 20, 200, 0.5, 3, 5);
    EXPECT_FALSE(cookie.onHit(50));

    cookie.levelUp();

    EXPECT_EQ(cookie.getLevel(), 2);
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

    EXPECT_EQ(plant.attack(Element::Water), 150);
    EXPECT_EQ(fire.attack(Element::Plant), 200);
    EXPECT_EQ(water.attack(Element::Fire), 170);
}

TEST(GingerbreadManTest, CriticalAttackWithoutTypeEffectiveness){
    GingerbreadMan cookie("Test", Element::Fire, Position::Front, 100, 0, 100, 0.5, 2, 5);
    EXPECT_EQ(cookie.attack(Element::Fire), 100);
    EXPECT_EQ(cookie.attack(Element::Fire), 150);
}

TEST(GingerbreadManTest, CriticalAttackWithTypeEffectiveness){
    GingerbreadMan cookie("Test", Element::Water, Position::Front, 100, 0, 100, 0.5, 2, 5);
    EXPECT_EQ(cookie.attack(Element::Fire), 170);
    EXPECT_EQ(cookie.attack(Element::Fire), 220);
}

TEST(GingerbreadManTest, Attacked){
    GingerbreadMan cookie("Test", Element::Fire, Position::Front, 100, 20, 200, 0.5, 3, 5);
    EXPECT_FALSE(cookie.onHit(50));
    EXPECT_EQ(cookie.getCurrHealth(), 170);

    EXPECT_TRUE(cookie.onHit(10));
    EXPECT_EQ(cookie.getCurrHealth(), 170);
}

TEST(GingerbreadManTest, AvoidAttack){
    GingerbreadMan cookie("Test", Element::Fire, Position::Front, 100, 10, 200, 0.5, 3, 2);
    EXPECT_FALSE(cookie.onHit(30));
    EXPECT_EQ(cookie.getCurrHealth(), 180);
    EXPECT_TRUE(cookie.onHit(30));
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

    EXPECT_EQ(plant.attack(Element::Water), 150);
    EXPECT_EQ(fire.attack(Element::Water), 100);
    EXPECT_EQ(water.attack(Element::Plant), 100);
}