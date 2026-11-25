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

TEST(PlantCookieTest, MillennialTreeCookieConstructor) {
    MillennialTreeCookie cookie;
    expectCookieStats(cookie, "Millennial Tree Cookie", Element::Plant, Position::Front, 200, 150, 1000, 1, 1000, 3, 5);
}

TEST(PlantCookieTest, MillennialTreeCookieLevelUp) {
    MillennialTreeCookie cookie;
    EXPECT_FALSE(cookie.onHit(350));
    EXPECT_EQ(cookie.getCurrHealth(), 950);
    cookie.levelUp();

    expectCookieStats(cookie, "Millennial Tree Cookie", Element::Plant, Position::Front, 350, 300, 1150, 2, 1150, 3, 5);
}

TEST(PlantCookieTest, MillennialTreeCookieAttack) {
    MillennialTreeCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 425);
}

TEST(PlantCookieTest, MillennialTreeCookieAttackUsesFloatingHealthRatio) {
    MillennialTreeCookie cookie;
    EXPECT_FALSE(cookie.onHit(350));
    EXPECT_EQ(cookie.getCurrHealth(), 950);

    EXPECT_EQ(cookie.attack(Element::Plant), 415);
}

TEST(PlantCookieTest, MillennialTreeCookieCriticalAttack) {
    MillennialTreeCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 425, 525);
}

TEST(PlantCookieTest, MillennialTreeCookieAttackAgainstWater) {
    MillennialTreeCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 525);
}

TEST(PlantCookieTest, MillennialTreeCookieCriticalAttackAgainstWater) {
    MillennialTreeCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Water, 525, 625);
}

TEST(PlantCookieTest, MillennialTreeCookieAttacked) {
    MillennialTreeCookie cookie;
    EXPECT_TRUE(cookie.onHit(250));
    EXPECT_EQ(cookie.getCurrHealth(), 1000);
    EXPECT_TRUE(cookie.onHit(300));
    EXPECT_EQ(cookie.getCurrHealth(), 1000);
    EXPECT_FALSE(cookie.onHit(350));
    EXPECT_EQ(cookie.getCurrHealth(), 950);
    EXPECT_EQ(cookie.getDefense(), 150);

    MillennialTreeCookie avoidedCookie;
    for (int attempt = 0; attempt < avoidedCookie.getMaxDodgeCount() - 1; ++attempt)
        EXPECT_FALSE(avoidedCookie.isDodged());
    EXPECT_TRUE(avoidedCookie.onHit(500));
    EXPECT_EQ(avoidedCookie.getCurrHealth(), 1000);
    EXPECT_EQ(avoidedCookie.getDefense(), 150);
}

TEST(PlantCookieTest, MillennialTreeCookieOnHitUsesFloatingHealthRatio) {
    MillennialTreeCookie cookie;
    EXPECT_FALSE(cookie.onHit(350));
    EXPECT_EQ(cookie.getCurrHealth(), 950);

    EXPECT_FALSE(cookie.onHit(300));
    EXPECT_EQ(cookie.getCurrHealth(), 943);
}

TEST(PlantCookieTest, WhiteLilyCookieConstructor) {
    WhiteLilyCookie cookie;
    expectCookieStats(cookie, "White Lily Cookie", Element::Plant, Position::Middle, 100, 100, 1500, 1, 1500, 2, 5);
}

TEST(PlantCookieTest, WhiteLilyCookieLevelUp) {
    WhiteLilyCookie cookie;
    cookie.levelUp();

    expectCookieStats(cookie, "White Lily Cookie", Element::Plant, Position::Middle, 200, 200, 1600, 2, 1600, 2, 5);
    expectCriticalAttackSequence(cookie, Element::Plant, 200, 560);
}

TEST(PlantCookieTest, WhiteLilyCookieAttack) {
    WhiteLilyCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 100);
}

TEST(PlantCookieTest, WhiteLilyCookieCriticalAttack) {
    WhiteLilyCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 100, 420);
}

TEST(PlantCookieTest, WhiteLilyCookieAttackAgainstWater) {
    WhiteLilyCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 150);
}

TEST(PlantCookieTest, WhiteLilyCookieCriticalAttackAgainstWater) {
    WhiteLilyCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Water, 150, 470);
}

TEST(PlantCookieTest, WhiteLilyCookieAttacked) {
    WhiteLilyCookie cookie;
    EXPECT_FALSE(cookie.onHit(250));
    EXPECT_EQ(cookie.getCurrHealth(), 1450);
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 0.3f);
}

TEST(PlantCookieTest, SilverbellCookieConstructor) {
    SilverbellCookie cookie;
    expectCookieStats(cookie, "Silverbell Cookie", Element::Plant, Position::Back, 200, 150, 900, 1, 900, 3, 8);
}

TEST(PlantCookieTest, SilverbellCookieLevelUp) {
    SilverbellCookie cookie;
    EXPECT_FALSE(cookie.onHit(300));
    EXPECT_EQ(cookie.getCurrHealth(), 752);
    cookie.levelUp();

    expectCookieStats(cookie, "Silverbell Cookie", Element::Plant, Position::Back, 350, 200, 1050, 2, 1050, 3, 8);
    EXPECT_EQ(cookie.getCurrHealth(), cookie.getHealth());
}

TEST(PlantCookieTest, SilverbellCookieAttack) {
    SilverbellCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Plant), 200);
}

TEST(PlantCookieTest, SilverbellCookieCriticalAttack) {
    SilverbellCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Plant, 200, 360);
}

TEST(PlantCookieTest, SilverbellCookieAttackAgainstWater) {
    SilverbellCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 300);
}

TEST(PlantCookieTest, SilverbellCookieCriticalAttackAgainstWater) {
    SilverbellCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Water, 300, 460);
}

TEST(PlantCookieTest, SilverbellCookieAttacked) {
    SilverbellCookie cookie;
    EXPECT_FALSE(cookie.onHit(300));
    EXPECT_EQ(cookie.getCurrHealth(), 752);
}