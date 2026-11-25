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

TEST(CookieTest, BurningSpiceCookieConstructor) {
    BurningSpiceCookie cookie;
    expectCookieStats(cookie, "Burning Spice Cookie", Element::Fire, Position::Front, 200, 100, 1000, 1, 1000, 3, 5);
}

TEST(CookieTest, BurningSpiceCookieLevelUp) {
    BurningSpiceCookie cookie;
    EXPECT_FALSE(cookie.attacked(150));
    cookie.levelUp();

    expectCookieStats(cookie, "Burning Spice Cookie", Element::Fire, Position::Front, 400, 100, 1150, 2, 1150, 3, 5);
    expectCriticalAttackSequence(cookie, Element::Fire, 450, 670);
    EXPECT_EQ(cookie.getDefense(), 100);
}

TEST(CookieTest, BurningSpiceCookieAttack) {
    BurningSpiceCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 250);
    EXPECT_EQ(cookie.getDefense(), 100);
}

TEST(CookieTest, BurningSpiceCookieCriticalAttack) {
    BurningSpiceCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Fire, 250, 350);
    EXPECT_EQ(cookie.getDefense(), 100);
}

TEST(CookieTest, BurningSpiceCookieAttackAgainstPlant) {
    BurningSpiceCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 390);
    EXPECT_EQ(cookie.getDefense(), 100);
}

TEST(CookieTest, BurningSpiceCookieCriticalAttackAgainstPlant) {
    BurningSpiceCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 390, 490);
    EXPECT_EQ(cookie.getDefense(), 100);
}

TEST(CookieTest, BurningSpiceCookieAttacked) {
    BurningSpiceCookie cookie;
    EXPECT_FALSE(cookie.attacked(150));
    EXPECT_EQ(cookie.getCurrHealth(), 950);
    EXPECT_TRUE(cookie.attacked(50));
    EXPECT_EQ(cookie.getCurrHealth(), 950);
}

TEST(CookieTest, ChiliPepperCookieConstructor) {
    ChiliPepperCookie cookie;
    expectCookieStats(cookie, "Chili Pepper Cookie", Element::Fire, Position::Middle, 200, 100, 700, 1, 700, 7, 3);
}

TEST(CookieTest, ChiliPepperCookieLevelUp) {
    ChiliPepperCookie cookie;
    EXPECT_FALSE(cookie.attacked(150));
    cookie.levelUp();

    expectCookieStats(cookie, "Chili Pepper Cookie", Element::Fire, Position::Middle, 300, 200, 800, 2, 800, 7, 3);
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 0.8f);
    expectCriticalAttackSequence(cookie, Element::Fire, 600, 840);
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 0.8f);
}

TEST(CookieTest, ChiliPepperCookieAttack) {
    ChiliPepperCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 400);
}

TEST(CookieTest, ChiliPepperCookieCriticalAttack) {
    ChiliPepperCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Fire, 400, 560);
}

TEST(CookieTest, ChiliPepperCookieAttackAgainstPlant) {
    ChiliPepperCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 540);
}

TEST(CookieTest, ChiliPepperCookieCriticalAttackAgainstPlant) {
    ChiliPepperCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 540, 700);
}

TEST(CookieTest, ChiliPepperCookieAttacked) {
    ChiliPepperCookie cookie;
    EXPECT_FALSE(cookie.attacked(150));
    EXPECT_EQ(cookie.getCurrHealth(), 650);
}

TEST(CookieTest, FireSpiritCookieConstructor) {
    FireSpiritCookie cookie;
    expectCookieStats(cookie, "Fire Spirit Cookie", Element::Fire, Position::Back, 500, 40, 200, 1, 200, 2, 7);
}

TEST(CookieTest, FireSpiritCookieLevelUp) {
    FireSpiritCookie cookie;
    EXPECT_FALSE(cookie.attacked(60));
    cookie.levelUp();

    expectCookieStats(cookie, "Fire Spirit Cookie", Element::Fire, Position::Back, 600, 40, 210, 2, 210, 2, 7);
    EXPECT_EQ(cookie.getCurrHealth(), cookie.getHealth());
    expectCriticalAttackSequence(cookie, Element::Fire, 600, 960);
    EXPECT_EQ(cookie.getCurrHealth(), 210);
}

TEST(CookieTest, FireSpiritCookieAttack) {
    FireSpiritCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 500);
}

TEST(CookieTest, FireSpiritCookieCriticalAttack) {
    FireSpiritCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Fire, 500, 750);
}

TEST(CookieTest, FireSpiritCookieAttackAgainstPlant) {
    FireSpiritCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 850);
}

TEST(CookieTest, FireSpiritCookieCriticalAttackAgainstPlant) {
    FireSpiritCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 850, 1100);
}

TEST(CookieTest, FireSpiritCookieAttacked) {
    FireSpiritCookie cookie;
    EXPECT_FALSE(cookie.attacked(60));
    EXPECT_EQ(cookie.getCurrHealth(), 180);
}