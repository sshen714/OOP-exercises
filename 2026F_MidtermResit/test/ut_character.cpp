#include "Character.hpp"

#include <gtest/gtest.h>

class TestCharacter : public Character {
public: 
    TestCharacter(std::string name, int damage, int defense, int health, int maxCritCount, int maxDodgeCount)
        : Character(name, damage, defense, health, maxCritCount, maxDodgeCount) {}
    void levelUp() override {}
    bool onHit(int) override { return false; }
};

TEST(CharacterTest, Constructor) {
    TestCharacter character("Test", 120, 35, 800, 3, 5);

    EXPECT_EQ(character.getName(), "Test");
    EXPECT_EQ(character.getLevel(), 1);
    EXPECT_EQ(character.getDamage(), 120);
    EXPECT_EQ(character.getDefense(), 35);
    EXPECT_EQ(character.getHealth(), 800);
    EXPECT_EQ(character.getCurrHealth(), 800);
    EXPECT_EQ(character.getMaxCritCount(), 3);
    EXPECT_EQ(character.getMaxDodgeCount(), 5);
}

TEST(CharacterTest, CountCritTimeWithTrigger) {
    TestCharacter character("Test", 1, 1, 1, 3, 5);
    EXPECT_FALSE(character.isCriticalHit());
    EXPECT_FALSE(character.isCriticalHit());
    EXPECT_TRUE(character.isCriticalHit());
}

TEST(CharacterTest, CountCritTimeWithoutTrigger) {
    TestCharacter character("Test", 1, 1, 1, 3, 5);
    EXPECT_FALSE(character.isCriticalHit());
    EXPECT_FALSE(character.isCriticalHit());
}

TEST(CharacterTest, CountAvoidTimeWithTrigger) {
    TestCharacter character("Test", 1, 1, 1, 3, 2);
    EXPECT_FALSE(character.isDodged());
    EXPECT_TRUE(character.isDodged());
}

TEST(CharacterTest, CountAvoidTimeWithoutTrigger) {
    TestCharacter character("Test", 1, 1, 1, 3, 2);
    EXPECT_FALSE(character.isDodged());
}