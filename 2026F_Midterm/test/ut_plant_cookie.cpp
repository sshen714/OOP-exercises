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

TEST(CookieTest, MillennialTreeCookieConstructor) {
    MillennialTreeCookie cookie;
    expectCookieStats(cookie, "Millennial Tree Cookie", Element::Plant, Position::Front, 200, 100, 1000, 1, 1000, 3, 5);
}

TEST(CookieTest, MillennialTreeCookieLevelUp) {
    MillennialTreeCookie cookie;
    EXPECT_FALSE(cookie.attacked(250));
    cookie.levelUp();

    expectCookieStats(cookie, "Millennial Tree Cookie", Element::Plant, Position::Front, 350, 250, 1150, 2, 1150, 3, 5);
}

TEST(CookieTest, MillennialTreeCookieAttack) {
    MillennialTreeCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 400);
}

TEST(CookieTest, MillennialTreeCookieCriticalAttack) {
    MillennialTreeCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 400, 500);
}

TEST(CookieTest, MillennialTreeCookieAttackAgainstWater) {
    MillennialTreeCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 460);
}

TEST(CookieTest, MillennialTreeCookieCriticalAttackAgainstWater) {
    MillennialTreeCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Water, 460, 560);
}

TEST(CookieTest, MillennialTreeCookieAttacked) {
    MillennialTreeCookie cookie;
    EXPECT_FALSE(cookie.attacked(250));
    EXPECT_EQ(cookie.getCurrHealth(), 950);
    EXPECT_EQ(cookie.getDefense(), 100);

    MillennialTreeCookie avoidedCookie;
    for (int attempt = 0; attempt < avoidedCookie.getAvoidTime() - 1; ++attempt)
        EXPECT_FALSE(avoidedCookie.countAvoidTime());
    EXPECT_TRUE(avoidedCookie.attacked(500));
    EXPECT_EQ(avoidedCookie.getCurrHealth(), 1000);
    EXPECT_EQ(avoidedCookie.getDefense(), 100);
}

TEST(CookieTest, WhiteLilyCookieConstructor) {
    WhiteLilyCookie cookie;
    expectCookieStats(cookie, "White Lily Cookie", Element::Plant, Position::Middle, 100, 100, 1500, 1, 1500, 2, 5);
}

TEST(CookieTest, WhiteLilyCookieLevelUp) {
    WhiteLilyCookie cookie;
    cookie.levelUp();

    expectCookieStats(cookie, "White Lily Cookie", Element::Plant, Position::Middle, 200, 200, 1600, 2, 1600, 2, 5);
    expectCriticalAttackSequence(cookie, Element::Plant, 200, 560);
}

TEST(CookieTest, WhiteLilyCookieAttack) {
    WhiteLilyCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 100);
}

TEST(CookieTest, WhiteLilyCookieCriticalAttack) {
    WhiteLilyCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 100, 420);
}

TEST(CookieTest, WhiteLilyCookieAttackAgainstWater) {
    WhiteLilyCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 130);
}

TEST(CookieTest, WhiteLilyCookieCriticalAttackAgainstWater) {
    WhiteLilyCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Water, 130, 450);
}

TEST(CookieTest, WhiteLilyCookieAttacked) {
    WhiteLilyCookie cookie;
    EXPECT_FALSE(cookie.attacked(250));
    EXPECT_EQ(cookie.getCurrHealth(), 1450);
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 0.5f);
}

TEST(CookieTest, SilverbellCookieConstructor) {
    SilverbellCookie cookie;
    expectCookieStats(cookie, "Silverbell Cookie", Element::Plant, Position::Back, 200, 150, 900, 1, 900, 3, 8);
}

TEST(CookieTest, SilverbellCookieLevelUp) {
    SilverbellCookie cookie;
    EXPECT_FALSE(cookie.attacked(300));
    EXPECT_EQ(cookie.getCurrHealth(), 752);
    cookie.levelUp();

    expectCookieStats(cookie, "Silverbell Cookie", Element::Plant, Position::Back, 350, 200, 1000, 2, 1000, 3, 8);
    EXPECT_EQ(cookie.getCurrHealth(), cookie.getHealth());
}

TEST(CookieTest, SilverbellCookieAttack) {
    SilverbellCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 200);
}

TEST(CookieTest, SilverbellCookieCriticalAttack) {
    SilverbellCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 200, 360);
}

TEST(CookieTest, SilverbellCookieAttackAgainstWater) {
    SilverbellCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 260);
}

TEST(CookieTest, SilverbellCookieCriticalAttackAgainstWater) {
    SilverbellCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Water, 260, 420);
}

TEST(CookieTest, SilverbellCookieAttacked) {
    SilverbellCookie cookie;
    EXPECT_FALSE(cookie.attacked(300));
    EXPECT_EQ(cookie.getCurrHealth(), 752);
}