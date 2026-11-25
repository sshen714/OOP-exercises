#include "Character.hpp"

#include <gtest/gtest.h>

class TestCharacter : public Character {
public: 
    TestCharacter(std::string name, int damage, int defense, int health, int critTime, int avoidTime)
        : Character(name, damage, defense, health, critTime, avoidTime) {}
    void levelUp() override {}
    bool attacked(int) override { return false; }
};

TEST(CharacterTest, Constructor) {
    TestCharacter character("Test", 120, 35, 800, 3, 5);

    EXPECT_EQ(character.getName(), "Test");
    EXPECT_EQ(character.getlevel(), 1);
    EXPECT_EQ(character.getDamage(), 120);
    EXPECT_EQ(character.getDefense(), 35);
    EXPECT_EQ(character.getHealth(), 800);
    EXPECT_EQ(character.getCurrHealth(), 800);
    EXPECT_EQ(character.getCritTime(), 3);
    EXPECT_EQ(character.getAvoidTime(), 5);
}

TEST(CharacterTest, CountCritTimeWithTrigger) {
    TestCharacter character("Test", 1, 1, 1, 3, 5);
    EXPECT_FALSE(character.countCritTime());
    EXPECT_FALSE(character.countCritTime());
    EXPECT_TRUE(character.countCritTime());
}

TEST(CharacterTest, CountCritTimeWithoutTrigger) {
    TestCharacter character("Test", 1, 1, 1, 3, 5);
    EXPECT_FALSE(character.countCritTime());
    EXPECT_FALSE(character.countCritTime());
}

TEST(CharacterTest, CountAvoidTimeWithTrigger) {
    TestCharacter character("Test", 1, 1, 1, 3, 2);
    EXPECT_FALSE(character.countAvoidTime());
    EXPECT_TRUE(character.countAvoidTime());
}

TEST(CharacterTest, CountAvoidTimeWithoutTrigger) {
    TestCharacter character("Test", 1, 1, 1, 3, 2);
    EXPECT_FALSE(character.countAvoidTime());
}