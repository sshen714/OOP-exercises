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

TEST(WaterCookieTest, CrimsonCoralCookieConstructor) {
    CrimsonCoralCookie cookie;
    expectCookieStats(cookie, "Crimson Coral Cookie", Element::Water, Position::Front, 250, 500, 100, 1, 100, 5, 10);
}

TEST(WaterCookieTest, CrimsonCoralCookieLevelUp) {
    CrimsonCoralCookie cookie;
    EXPECT_FALSE(cookie.onHit(550));
    cookie.levelUp();

    expectCookieStats(cookie, "Crimson Coral Cookie", Element::Water, Position::Front, 350, 600, 200, 2, 200, 5, 10);
}

TEST(WaterCookieTest, CrimsonCoralCookieAttack) {
    CrimsonCoralCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 850);
    EXPECT_EQ(cookie.getDefense(), 550);
}

TEST(WaterCookieTest, CrimsonCoralCookieCriticalAttack) {
    CrimsonCoralCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 850);
    EXPECT_EQ(cookie.getDefense(), 550);
    EXPECT_EQ(cookie.attack(Element::Water), 900);
    EXPECT_EQ(cookie.getDefense(), 605);
    EXPECT_EQ(cookie.attack(Element::Water), 955);
    EXPECT_EQ(cookie.getDefense(), 665);
    EXPECT_EQ(cookie.attack(Element::Water), 1015);
    EXPECT_EQ(cookie.getDefense(), 731);
    EXPECT_EQ(cookie.attack(Element::Water), 1206);
    EXPECT_EQ(cookie.getDefense(), 804);
}

TEST(WaterCookieTest, CrimsonCoralCookieAttackAgainstFire) {
    CrimsonCoralCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 1025);
    EXPECT_EQ(cookie.getDefense(), 550);
}

TEST(WaterCookieTest, CrimsonCoralCookieCriticalAttackAgainstFire) {
    CrimsonCoralCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 1025);
    EXPECT_EQ(cookie.getDefense(), 550);
    EXPECT_EQ(cookie.attack(Element::Fire), 1075);
    EXPECT_EQ(cookie.getDefense(), 605);
    EXPECT_EQ(cookie.attack(Element::Fire), 1130);
    EXPECT_EQ(cookie.getDefense(), 665);
    EXPECT_EQ(cookie.attack(Element::Fire), 1190);
    EXPECT_EQ(cookie.getDefense(), 731);
    EXPECT_EQ(cookie.attack(Element::Fire), 1381);
    EXPECT_EQ(cookie.getDefense(), 804);
}

TEST(WaterCookieTest, CrimsonCoralCookieAttacked) {
    CrimsonCoralCookie cookie;
    EXPECT_FALSE(cookie.onHit(550));
    EXPECT_EQ(cookie.getCurrHealth(), 50);
}

TEST(WaterCookieTest, SeaFairyCookieConstructor) {
    SeaFairyCookie cookie;
    expectCookieStats(cookie, "Sea Fairy Cookie", Element::Water, Position::Middle, 200, 300, 1000, 1, 1000, 3, 5);
}

TEST(WaterCookieTest, SeaFairyCookieLevelUp) {
    SeaFairyCookie cookie;
    EXPECT_FALSE(cookie.onHit(400));
    EXPECT_EQ(cookie.attack(Element::Water), 200);
    cookie.levelUp();

    expectCookieStats(cookie, "Sea Fairy Cookie", Element::Water, Position::Middle, 300, 450, 1160, 2, 1160, 2, 5);
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 0.4f);
    expectCriticalAttackSequence(cookie, Element::Water, 300, 600);
    EXPECT_FLOAT_EQ(cookie.getCritDamage(), 0.4f);
}

TEST(WaterCookieTest, SeaFairyCookieAttack) {
    SeaFairyCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 200);
}

TEST(WaterCookieTest, SeaFairyCookieCriticalAttack) {
    SeaFairyCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Water, 200, 350);
}

TEST(WaterCookieTest, SeaFairyCookieAttackAgainstFire) {
    SeaFairyCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 340);
}

TEST(WaterCookieTest, SeaFairyCookieCriticalAttackAgainstFire) {
    SeaFairyCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Fire, 340, 490);
}

TEST(WaterCookieTest, SeaFairyCookieAttacked) {
    SeaFairyCookie cookie;
    EXPECT_FALSE(cookie.onHit(400));
    EXPECT_EQ(cookie.getCurrHealth(), 900);
}

TEST(WaterCookieTest, SeltzerCookieConstructor) {
    SeltzerCookie cookie;
    expectCookieStats(cookie, "Seltzer Cookie", Element::Water, Position::Back, 200, 450, 700, 1, 700, 2, 3);
}

TEST(WaterCookieTest, SeltzerCookieLevelUp) {
    SeltzerCookie cookie;
    EXPECT_FALSE(cookie.onHit(500));
    cookie.levelUp();

    expectCookieStats(cookie, "Seltzer Cookie", Element::Water, Position::Back, 300, 550, 800, 2, 800, 2, 3);
}

TEST(WaterCookieTest, SeltzerCookieAttack) {
    SeltzerCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Water), 200);
}

TEST(WaterCookieTest, SeltzerCookieCriticalAttack) {
    SeltzerCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Water, 200, 340);
}

TEST(WaterCookieTest, SeltzerCookieAttackAgainstFire) {
    SeltzerCookie cookie;
    EXPECT_EQ(cookie.attack(Element::Fire), 340);
}

TEST(WaterCookieTest, SeltzerCookieCriticalAttackAgainstFire) {
    SeltzerCookie cookie;
    expectCriticalAttackSequence(cookie, Element::Fire, 340, 480);
}

TEST(WaterCookieTest, SeltzerCookieAttacked) {
    SeltzerCookie cookie;
    EXPECT_FALSE(cookie.onHit(500));
    EXPECT_EQ(cookie.getCurrHealth(), 656);

    EXPECT_TRUE(cookie.onHit(400));
    EXPECT_EQ(cookie.getCurrHealth(), 657);

    EXPECT_TRUE(cookie.onHit(500));
    EXPECT_EQ(cookie.getCurrHealth(), 658);
}