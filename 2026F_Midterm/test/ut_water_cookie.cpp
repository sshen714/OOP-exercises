#include "BurningSpiceCookie.hpp"
#include "ChiliPepperCookie.hpp"
#include "CrimsonCoralCookie.hpp"
#include "FireSpiritCookie.hpp"
#include "GingerbreadMan.hpp"
#include "MillennialTreeCookie.hpp"
#include "SeaFairyCookie.hpp"
#include "SeltzerCookie.hpp"
#include "SilverbellCookie.hpp"
#include "WhiteLilyCookie.hpp"

#include <gtest/gtest.h>

#include <string>

namespace {

void expectCookieStats(
    const GingerbreadMan& cookie,
    const std::string& name,
    Element element,
    Position position,
    int damage,
    int defense,
    int health,
    int level,
    int currHealth,
    int critTime,
    int avoidTime
) {
    EXPECT_EQ(cookie.getName(), name);
    EXPECT_EQ(cookie.getElementType(), element);
    EXPECT_EQ(cookie.getPosition(), position);
    EXPECT_EQ(cookie.getDamage(), damage);
    EXPECT_EQ(cookie.getDefense(), defense);
    EXPECT_EQ(cookie.getHealth(), health);
    EXPECT_EQ(cookie.getlevel(), level);
    EXPECT_EQ(cookie.getCurrHealth(), currHealth);
    EXPECT_EQ(cookie.getCritTime(), critTime);
    EXPECT_EQ(cookie.getAvoidTime(), avoidTime);
}

void expectCriticalAttackSequence(
    GingerbreadMan& cookie,
    Element enemyType,
    int normalDamage,
    int criticalDamage
) {
    for (int strike = 1; strike < cookie.getCritTime(); ++strike)
        EXPECT_EQ(cookie.attack(enemyType), normalDamage);
    EXPECT_NEAR(cookie.attack(enemyType), criticalDamage, 1);
}

}

TEST(CookieTest, CrimsonCoralCookieConstructor) {
    CrimsonCoralCookie cookie;
    expectCookieStats(cookie, "Crimson Coral Cookie", Element::Water, Position::Front, 200, 500, 100, 1, 100, 3, 10);
}

TEST(CookieTest, CrimsonCoralCookieLevelUp) {
    CrimsonCoralCookie cookie;
    EXPECT_FALSE(cookie.attacked(550));
    cookie.levelUp();

    expectCookieStats(cookie, "Crimson Coral Cookie", Element::Water, Position::Front, 300, 600, 200, 2, 200, 3, 10);
}

TEST(CookieTest, CrimsonCoralCookieAttack) {
    CrimsonCoralCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 800);
    EXPECT_EQ(cookie.getDefense(), 550);
}

TEST(CookieTest, CrimsonCoralCookieCriticalAttack) {
    CrimsonCoralCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 800);
    EXPECT_EQ(cookie.getDefense(), 550);
    EXPECT_EQ(cookie.attack(Element::Water), 850);
    EXPECT_EQ(cookie.getDefense(), 600);
    EXPECT_EQ(cookie.attack(Element::Water), 1000);
    EXPECT_EQ(cookie.getDefense(), 650);
}

TEST(CookieTest, CrimsonCoralCookieAttackAgainstFire) {
    CrimsonCoralCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 900);
    EXPECT_EQ(cookie.getDefense(), 550);
}

TEST(CookieTest, CrimsonCoralCookieCriticalAttackAgainstFire) {
    CrimsonCoralCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 900);
    EXPECT_EQ(cookie.getDefense(), 550);
    EXPECT_EQ(cookie.attack(Element::Fire), 950);
    EXPECT_EQ(cookie.getDefense(), 600);
    EXPECT_EQ(cookie.attack(Element::Fire), 1100);
    EXPECT_EQ(cookie.getDefense(), 650);
}

TEST(CookieTest, CrimsonCoralCookieAttacked) {
    CrimsonCoralCookie cookie;
    EXPECT_FALSE(cookie.attacked(550));
    EXPECT_EQ(cookie.getCurrHealth(), 50);
}

TEST(CookieTest, SeaFairyCookieConstructor) {
    SeaFairyCookie cookie;
    expectCookieStats(cookie, "Sea Fairy Cookie", Element::Water, Position::Middle, 200, 300, 1000, 1, 1000, 3, 5);
}

TEST(CookieTest, SeaFairyCookieLevelUp) {
    SeaFairyCookie cookie;
    EXPECT_FALSE(cookie.attacked(400));
    cookie.levelUp();

    expectCookieStats(cookie, "Sea Fairy Cookie", Element::Water, Position::Middle, 300, 500, 1140, 2, 1140, 3, 5);
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 0.5f);
    expectCriticalAttackSequence(cookie, Element::Water, 300, 700);
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 0.5f);
}

TEST(CookieTest, SeaFairyCookieAttack) {
    SeaFairyCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 200);
}

TEST(CookieTest, SeaFairyCookieCriticalAttack) {
    SeaFairyCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Water, 200, 350);
}

TEST(CookieTest, SeaFairyCookieAttackAgainstFire) {
    SeaFairyCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 300);
}

TEST(CookieTest, SeaFairyCookieCriticalAttackAgainstFire) {
    SeaFairyCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Fire, 300, 450);
}

TEST(CookieTest, SeaFairyCookieAttacked) {
    SeaFairyCookie cookie;
    EXPECT_FALSE(cookie.attacked(400));
    EXPECT_EQ(cookie.getCurrHealth(), 900);
}

TEST(CookieTest, SeltzerCookieConstructor) {
    SeltzerCookie cookie;
    expectCookieStats(cookie, "Seltzer Cookie", Element::Water, Position::Back, 100, 400, 700, 1, 700, 2, 3);
}

TEST(CookieTest, SeltzerCookieLevelUp) {
    SeltzerCookie cookie;
    EXPECT_FALSE(cookie.attacked(500));
    cookie.levelUp();

    expectCookieStats(cookie, "Seltzer Cookie", Element::Water, Position::Back, 200, 500, 800, 2, 800, 2, 3);
}

TEST(CookieTest, SeltzerCookieAttack) {
    SeltzerCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 100);
}

TEST(CookieTest, SeltzerCookieCriticalAttack) {
    SeltzerCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Water, 100, 180);
}

TEST(CookieTest, SeltzerCookieAttackAgainstFire) {
    SeltzerCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 150);
}

TEST(CookieTest, SeltzerCookieCriticalAttackAgainstFire) {
    SeltzerCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Fire, 150, 230);
}

TEST(CookieTest, SeltzerCookieAttacked) {
    SeltzerCookie cookie;
    EXPECT_FALSE(cookie.attacked(500));
    EXPECT_EQ(cookie.getCurrHealth(), 605);

    EXPECT_TRUE(cookie.attacked(400));
    EXPECT_EQ(cookie.getCurrHealth(), 606);

    EXPECT_TRUE(cookie.attacked(500));
    EXPECT_EQ(cookie.getCurrHealth(), 607);
}