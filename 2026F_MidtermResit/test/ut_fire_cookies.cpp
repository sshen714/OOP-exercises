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
    int maxCritCount,
    int maxDodgeCount
) {
    EXPECT_EQ(cookie.getName(), name);
    EXPECT_EQ(cookie.getElementType(), element);
    EXPECT_EQ(cookie.getPosition(), position);
    EXPECT_EQ(cookie.getDamage(), damage);
    EXPECT_EQ(cookie.getDefense(), defense);
    EXPECT_EQ(cookie.getHealth(), health);
    EXPECT_EQ(cookie.getLevel(), level);
    EXPECT_EQ(cookie.getCurrHealth(), currHealth);
    EXPECT_EQ(cookie.getMaxCritCount(), maxCritCount);
    EXPECT_EQ(cookie.getMaxDodgeCount(), maxDodgeCount);
}

void expectCriticalAttackSequence(
    GingerbreadMan& cookie,
    Element enemyType,
    int normalDamage,
    int criticalDamage
) {
    for (int strike = 1; strike < cookie.getMaxCritCount(); ++strike)
        EXPECT_EQ(cookie.attack(enemyType), normalDamage);
    EXPECT_NEAR(cookie.attack(enemyType), criticalDamage, 1);
}

}

TEST(FireCookieTest, BurningSpiceCookieConstructor) {
    BurningSpiceCookie cookie;
    expectCookieStats(cookie, "Burning Spice Cookie", Element::Fire, Position::Front, 200, 80, 1000, 1, 1000, 3, 5);
}

TEST(FireCookieTest, BurningSpiceCookieLevelUp) {
    BurningSpiceCookie cookie;
    EXPECT_FALSE(cookie.onHit(150));
    cookie.levelUp();

    expectCookieStats(cookie, "Burning Spice Cookie", Element::Fire, Position::Front, 450, 80, 1220, 2, 1220, 3, 5);
    expectCriticalAttackSequence(cookie, Element::Fire, 475, 736);
    EXPECT_EQ(cookie.getDefense(), 80);
}

TEST(FireCookieTest, BurningSpiceCookieAttack) {
    BurningSpiceCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 225);
    EXPECT_EQ(cookie.getDefense(), 80);
}

TEST(FireCookieTest, BurningSpiceCookieCriticalAttack) {
    BurningSpiceCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Fire, 225, 338);
    EXPECT_EQ(cookie.getDefense(), 80);
}

TEST(FireCookieTest, BurningSpiceCookieAttackAgainstPlant) {
    BurningSpiceCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 450);
    EXPECT_EQ(cookie.getDefense(), 80);
}

TEST(FireCookieTest, BurningSpiceCookieCriticalAttackAgainstPlant) {
    BurningSpiceCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 450, 563);
    EXPECT_EQ(cookie.getDefense(), 80);
}

TEST(FireCookieTest, BurningSpiceCookieAttacked) {
    BurningSpiceCookie cookie;
    EXPECT_FALSE(cookie.onHit(150));
    EXPECT_EQ(cookie.getCurrHealth(), 930);
    EXPECT_TRUE(cookie.onHit(50));
    EXPECT_EQ(cookie.getCurrHealth(), 930);
}

TEST(FireCookieTest, ChiliPepperCookieConstructor) {
    ChiliPepperCookie cookie;
    expectCookieStats(cookie, "Chili Pepper Cookie", Element::Fire, Position::Middle, 200, 100, 900, 1, 900, 7, 4);
}

TEST(FireCookieTest, ChiliPepperCookieLevelUp) {
    ChiliPepperCookie cookie;
    EXPECT_FALSE(cookie.onHit(150));
    cookie.levelUp();

    expectCookieStats(cookie, "Chili Pepper Cookie", Element::Fire, Position::Middle, 400, 200, 1000, 2, 1000, 7, 4);
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 0.9f);
    expectCriticalAttackSequence(cookie, Element::Fire, 800, 1160);
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 0.9f);
}

TEST(FireCookieTest, ChiliPepperCookieAttack) {
    ChiliPepperCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 400);
}

TEST(FireCookieTest, ChiliPepperCookieAttackUsesFloatingHealthRatio) {
    ChiliPepperCookie cookie;
    EXPECT_FALSE(cookie.onHit(150));
    EXPECT_EQ(cookie.getCurrHealth(), 850);

    EXPECT_EQ(cookie.attack(Element::Fire), 388);
}

TEST(FireCookieTest, ChiliPepperCookieCriticalAttack) {
    ChiliPepperCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Fire, 400, 560);
}

TEST(FireCookieTest, ChiliPepperCookieAttackAgainstPlant) {
    ChiliPepperCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 600);
}

TEST(FireCookieTest, ChiliPepperCookieCriticalAttackAgainstPlant) {
    ChiliPepperCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 600, 760);
}

TEST(FireCookieTest, ChiliPepperCookieAttacked) {
    ChiliPepperCookie cookie;
    EXPECT_FALSE(cookie.onHit(150));
    EXPECT_EQ(cookie.getCurrHealth(), 850);
}

TEST(FireCookieTest, FireSpiritCookieConstructor) {
    FireSpiritCookie cookie;
    expectCookieStats(cookie, "Fire Spirit Cookie", Element::Fire, Position::Back, 500, 20, 200, 1, 200, 2, 7);
}

TEST(FireCookieTest, FireSpiritCookieLevelUp) {
    FireSpiritCookie cookie;
    EXPECT_FALSE(cookie.onHit(60));
    cookie.levelUp();

    expectCookieStats(cookie, "Fire Spirit Cookie", Element::Fire, Position::Back, 600, 25, 220, 2, 220, 2, 7);
    EXPECT_EQ(cookie.getCurrHealth(), cookie.getHealth());
    expectCriticalAttackSequence(cookie, Element::Fire, 600, 960);
    EXPECT_EQ(cookie.getCurrHealth(), 220);
}

TEST(FireCookieTest, FireSpiritCookieAttack) {
    FireSpiritCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 500);
}

TEST(FireCookieTest, FireSpiritCookieCriticalAttack) {
    FireSpiritCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Fire, 500, 750);
}

TEST(FireCookieTest, FireSpiritCookieAttackAgainstPlant) {
    FireSpiritCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 1000);
}

TEST(FireCookieTest, FireSpiritCookieCriticalAttackAgainstPlant) {
    FireSpiritCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 1000, 1250);
}

TEST(FireCookieTest, FireSpiritCookieAttacked) {
    FireSpiritCookie cookie;
    EXPECT_FALSE(cookie.onHit(60));
    EXPECT_EQ(cookie.getCurrHealth(), 160);
}