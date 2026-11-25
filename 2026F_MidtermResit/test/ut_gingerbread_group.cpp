#include "GingerbreadGroup.hpp"
#include "BurningSpiceCookie.hpp"
#include "CrimsonCoralCookie.hpp"
#include "FireSpiritCookie.hpp"
#include "MillennialTreeCookie.hpp"
#include "SilverbellCookie.hpp"
#include "WhiteLilyCookie.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>
#include <vector>

TEST(GingerbreadGroupTest, Constructor) {
    EXPECT_THROW(GingerbreadGroup(2), std::invalid_argument);
    EXPECT_NO_THROW(GingerbreadGroup(3));
    EXPECT_NO_THROW(GingerbreadGroup(9));
    EXPECT_THROW(GingerbreadGroup(10), std::invalid_argument);
}

TEST(GingerbreadGroupTest, AttackWithNoCriticalCookie) {
    GingerbreadGroup group(3);
    GingerbreadMan attacker("Attacker", Element::Fire, Position::Front, 100, 0, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(attacker));
    std::vector<Element> enemyTypes{Element::Fire, Element::Water};

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{100, 100}));
}

TEST(GingerbreadGroupTest, AttackWithSomeCriticalCookie) {
    GingerbreadGroup group(3);
    GingerbreadMan attacker("Attacker", Element::Fire, Position::Front, 100, 0, 100, 0.5, 1, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(attacker));
    std::vector<Element> enemyTypes{Element::Fire, Element::Water, Element::Plant};

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{150, 0, 0}));
}

TEST(GingerbreadGroupTest, MembersTakeTurnsAndCurrIndexWraps) {
    GingerbreadGroup group(3);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Front", Element::Fire, Position::Front, 100, 0, 100, 0.5, 5, 5
    ));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Middle", Element::Fire, Position::Middle, 200, 0, 100, 0.5, 5, 5
    ));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Back", Element::Fire, Position::Back, 300, 0, 100, 0.5, 5, 5
    ));
    std::vector<Element> enemyTypes{Element::Fire};

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{100}));
    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{200}));
    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{300}));
    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{100}));
}

TEST(GingerbreadGroupTest, MiddleAndBackAttackTheirAllowedEnemyPositions) {
    GingerbreadGroup group(3);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Middle", Element::Fire, Position::Middle, 200, 0, 100, 0.5, 5, 5
    ));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Back", Element::Fire, Position::Back, 300, 0, 100, 0.5, 5, 5
    ));
    std::vector<Element> enemyTypes(6, Element::Fire);

    EXPECT_EQ(
        group.attack(enemyTypes),
        (std::vector<int>{200, 200, 200, 200, 0, 0})
    );
    EXPECT_EQ(
        group.attack(enemyTypes),
        (std::vector<int>{0, 0, 300, 300, 300, 300})
    );
}

TEST(GingerbreadGroupTest, AttackPreservesCookieOverride) {
    GingerbreadGroup group(3);
    CrimsonCoralCookie cookie;
    group.addGingerbreadMan(std::make_shared<CrimsonCoralCookie>(cookie));
    std::vector<Element> enemyTypes{Element::Water};

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{850}));
}

TEST(GingerbreadGroupTest, OnHitPreservesCookieOverride) {
    GingerbreadGroup group(3);
    WhiteLilyCookie cookie;
    group.addGingerbreadMan(std::make_shared<WhiteLilyCookie>(cookie));
    std::vector<int> damages{150};

    group.onHit(damages);

    EXPECT_EQ(group.getGingerbreadMan(0)->getCurrHealth(), 1500);
}

TEST(GingerbreadGroupTest, GetterPreservesCookieTypeAndLevelUpOverride) {
    GingerbreadGroup group(3);
    BurningSpiceCookie cookie;
    group.addGingerbreadMan(std::make_shared<BurningSpiceCookie>(cookie));

    group.getGingerbreadMan(0)->levelUp();

    EXPECT_EQ(group.getGingerbreadMan(0)->getDamage(), 450);
    EXPECT_EQ(group.getGingerbreadMan(0)->getHealth(), 1220);
}

TEST(GingerbreadGroupTest, AttackedWithNoAvoidCookie) {
    GingerbreadGroup group(3);
    GingerbreadMan member("Member", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(member));
    std::vector<int> damages{30};

    group.onHit(damages);
    EXPECT_EQ(group.getGingerbreadMan(0)->getCurrHealth(), 80);
}

TEST(GingerbreadGroupTest, AttackedWithSomeAvoidCookie) {
    GingerbreadGroup group(3);
    GingerbreadMan member("Member", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 2);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(member));
    std::vector<int> damages{30};

    group.onHit(damages);
    EXPECT_EQ(group.getGingerbreadMan(0)->getCurrHealth(), 80);
    group.onHit(damages);
    EXPECT_EQ(group.getGingerbreadMan(0)->getCurrHealth(), 80);
}

TEST(GingerbreadGroupTest, OnHitRejectsDamageVectorsWithWrongLength) {
    GingerbreadGroup group(3);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Member", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5
    ));
    std::vector<int> noDamages;
    std::vector<int> tooManyDamages{0, 0};

    EXPECT_THROW(group.onHit(noDamages), std::invalid_argument);
    EXPECT_THROW(group.onHit(tooManyDamages), std::invalid_argument);
}

TEST(GingerbreadGroupTest, OnHitAutomaticallyRemovesDeadMembers) {
    GingerbreadGroup group(3);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Dead", Element::Fire, Position::Front, 100, 0, 50, 0.5, 3, 5
    ));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Alive", Element::Fire, Position::Middle, 100, 0, 100, 0.5, 3, 5
    ));
    std::vector<int> damages{100, 0};

    group.onHit(damages);

    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Alive");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, AddGingerbreadManRejectsDuplicateNames) {
    GingerbreadGroup group(3);
    GingerbreadMan first("Same", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan duplicate("Same", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(first));

    EXPECT_THROW(group.addGingerbreadMan(std::make_shared<GingerbreadMan>(duplicate)), std::invalid_argument);
    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Same");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, AddGingerbreadManRejectsNullPointer) {
    GingerbreadGroup group(3);

    EXPECT_THROW(
        group.addGingerbreadMan(std::shared_ptr<GingerbreadMan>{}),
        std::invalid_argument
    );
    EXPECT_THROW(group.getGingerbreadMan(0), std::out_of_range);
}

TEST(GingerbreadGroupTest, AddGingerbreadManRejectsFullPositions) {
    GingerbreadGroup group(3);
    GingerbreadMan first("First", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan second("Second", Element::Water, Position::Front, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(first));

    EXPECT_THROW(group.addGingerbreadMan(std::make_shared<GingerbreadMan>(second)), std::invalid_argument);
    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "First");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, AddGingerbreadMan) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan middle("Middle", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan back("Back", Element::Plant, Position::Back, 100, 10, 100, 0.5, 3, 5);

    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(front));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(middle));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(back));

    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Front");
    EXPECT_EQ(group.getGingerbreadMan(1)->getName(), "Middle");
    EXPECT_EQ(group.getGingerbreadMan(2)->getName(), "Back");
}

TEST(GingerbreadGroupTest, ReplaceGingerbreadManRejectsDuplicateNames) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan middle("Middle", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan duplicate("Middle", Element::Plant, Position::Front, 200, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(front));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(middle));

    EXPECT_THROW(group.replaceGingerbreadMan(0, std::make_shared<GingerbreadMan>(duplicate)), std::invalid_argument);
    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Front");
}

TEST(GingerbreadGroupTest, ReplaceGingerbreadManRejectsInvalidIndex) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(front));

    EXPECT_THROW(group.replaceGingerbreadMan(-1, std::make_shared<GingerbreadMan>(front)), std::out_of_range);
    EXPECT_THROW(group.replaceGingerbreadMan(1, std::make_shared<GingerbreadMan>(front)), std::out_of_range);
    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Front");
}

TEST(GingerbreadGroupTest, ReplaceGingerbreadManRejectsNullPointer) {
    GingerbreadGroup group(3);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5
    ));

    EXPECT_THROW(
        group.replaceGingerbreadMan(0, std::shared_ptr<GingerbreadMan>{}),
        std::invalid_argument
    );
    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Front");
}

TEST(GingerbreadGroupTest, ReplaceGingerbreadManRejectsWrongPositionCookies) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan middle("Middle", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(front));

    EXPECT_THROW(group.replaceGingerbreadMan(0, std::make_shared<GingerbreadMan>(middle)), std::invalid_argument);
    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Front");
}

TEST(GingerbreadGroupTest, ReplaceGingerbreadMan) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan replacement("Replacement", Element::Plant, Position::Front, 200, 20, 200, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(front));

    group.replaceGingerbreadMan(0, std::make_shared<GingerbreadMan>(replacement));

    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Replacement");
    EXPECT_EQ(group.getGingerbreadMan(0)->getElementType(), Element::Plant);
    EXPECT_EQ(group.getGingerbreadMan(0)->getDamage(), 200);
    EXPECT_EQ(group.getGingerbreadMan(0)->getDefense(), 20);
    EXPECT_EQ(group.getGingerbreadMan(0)->getHealth(), 200);
}

TEST(GingerbreadGroupTest, ReplaceGingerbreadManAllowsSameNameAtSameIndex) {
    GingerbreadGroup group(3);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Same", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5
    ));

    group.replaceGingerbreadMan(
        0,
        std::make_shared<GingerbreadMan>(
            "Same", Element::Plant, Position::Front, 200, 20, 200, 0.5, 3, 5
        )
    );

    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Same");
    EXPECT_EQ(group.getGingerbreadMan(0)->getElementType(), Element::Plant);
    EXPECT_EQ(group.getGingerbreadMan(0)->getDamage(), 200);
}

TEST(GingerbreadGroupTest, SortByHealth) {
    GingerbreadGroup group(3);
    MillennialTreeCookie front;
    WhiteLilyCookie middle;
    SilverbellCookie back;
    group.addGingerbreadMan(std::make_shared<MillennialTreeCookie>(front));
    group.addGingerbreadMan(std::make_shared<WhiteLilyCookie>(middle));
    group.addGingerbreadMan(std::make_shared<SilverbellCookie>(back));

    group.sortByHealth();

    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "White Lily Cookie");
    EXPECT_EQ(group.getGingerbreadMan(1)->getName(), "Millennial Tree Cookie");
    EXPECT_EQ(group.getGingerbreadMan(2)->getName(), "Silverbell Cookie");
}

TEST(GingerbreadGroupTest, SortByDamage) {
    GingerbreadGroup group(3);
    MillennialTreeCookie front;
    WhiteLilyCookie middle;
    SilverbellCookie back;
    group.addGingerbreadMan(std::make_shared<MillennialTreeCookie>(front));
    group.addGingerbreadMan(std::make_shared<WhiteLilyCookie>(middle));
    group.addGingerbreadMan(std::make_shared<SilverbellCookie>(back));

    group.sortByDamage();

    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Millennial Tree Cookie");
    EXPECT_EQ(group.getGingerbreadMan(1)->getName(), "Silverbell Cookie");
    EXPECT_EQ(group.getGingerbreadMan(2)->getName(), "White Lily Cookie");
}

TEST(GingerbreadGroupTest, SortByDefense) {
    GingerbreadGroup group(3);
    MillennialTreeCookie front;
    WhiteLilyCookie middle;
    SilverbellCookie back;
    group.addGingerbreadMan(std::make_shared<MillennialTreeCookie>(front));
    group.addGingerbreadMan(std::make_shared<WhiteLilyCookie>(middle));
    group.addGingerbreadMan(std::make_shared<SilverbellCookie>(back));

    group.sortByDefense();

    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Millennial Tree Cookie");
    EXPECT_EQ(group.getGingerbreadMan(1)->getName(), "Silverbell Cookie");
    EXPECT_EQ(group.getGingerbreadMan(2)->getName(), "White Lily Cookie");
}

TEST(GingerbreadGroupTest, CountCombatPower) {
    GingerbreadGroup group(3);
    MillennialTreeCookie tree;
    WhiteLilyCookie lily;
    group.addGingerbreadMan(std::make_shared<MillennialTreeCookie>(tree));
    group.addGingerbreadMan(std::make_shared<WhiteLilyCookie>(lily));

    EXPECT_EQ(group.countCombatPower(), 3050);
}

TEST(GingerbreadGroupTest, RemoveDeadGingerbreadManKeepsLivingMembers) {
    GingerbreadGroup group(3);
    GingerbreadMan living("Living", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan dead("Dead", Element::Water, Position::Middle, 100, 0, 50, 0.5, 3, 100);
    EXPECT_FALSE(dead.onHit(100));
    EXPECT_LE(dead.getCurrHealth(), 0);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(living));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(dead));

    group.removeDeadGingerbreadMan();

    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Living");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, RemoveGingerbreadManByName) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan middle("Middle", Element::Water, Position::Middle, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(front));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(middle));

    group.removeGingerbreadMan("Front");

    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Middle");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, RemovingBeforeNextAttackerKeepsThatAttacker) {
    GingerbreadGroup group(3);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Front", Element::Fire, Position::Front, 100, 0, 100, 0.5, 3, 5
    ));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Middle", Element::Fire, Position::Middle, 200, 0, 100, 0.5, 3, 5
    ));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Back", Element::Fire, Position::Back, 300, 0, 100, 0.5, 3, 5
    ));
    std::vector<Element> enemyTypes{Element::Fire};

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{100}));
    group.removeGingerbreadMan("Front");
    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{200}));
}

TEST(GingerbreadGroupTest, RemovingNextAttackerAdvancesToNextMember) {
    GingerbreadGroup group(3);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Front", Element::Fire, Position::Front, 100, 0, 100, 0.5, 3, 5
    ));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Middle", Element::Fire, Position::Middle, 200, 0, 100, 0.5, 3, 5
    ));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(
        "Back", Element::Fire, Position::Back, 300, 0, 100, 0.5, 3, 5
    ));
    std::vector<Element> enemyTypes{Element::Fire};

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{100}));
    group.removeGingerbreadMan("Middle");
    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{300}));
}

TEST(GingerbreadGroupTest, RemovingDeadNextAttackerAdvancesToNextMember) {
    GingerbreadGroup group(3);
    auto front = std::make_shared<GingerbreadMan>(
        "Front", Element::Fire, Position::Front, 100, 0, 100, 0.5, 3, 5
    );
    auto middle = std::make_shared<GingerbreadMan>(
        "Middle", Element::Fire, Position::Middle, 200, 0, 50, 0.5, 3, 5
    );
    auto back = std::make_shared<GingerbreadMan>(
        "Back", Element::Fire, Position::Back, 300, 0, 100, 0.5, 3, 5
    );
    group.addGingerbreadMan(front);
    group.addGingerbreadMan(middle);
    group.addGingerbreadMan(back);
    std::vector<Element> enemyTypes{Element::Fire};

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{100}));
    EXPECT_FALSE(middle->onHit(100));
    group.removeDeadGingerbreadMan();
    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{300}));
}

TEST(GingerbreadGroupTest, RemoveGingerbreadManByElement) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Plant, Position::Front, 100, 10, 100, 0.5, 3, 5);
    GingerbreadMan middle("Middle", Element::Water, Position::Middle, 200, 10, 100, 0.5, 3, 5);
    GingerbreadMan back("Back", Element::Plant, Position::Back, 300, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(front));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(middle));
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(back));
    std::vector<Element> enemyTypes{Element::Plant};

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{100}));
    group.removeGingerbreadMan(Element::Plant);

    EXPECT_EQ(group.attack(enemyTypes), (std::vector<int>{200}));
    EXPECT_EQ(group.getGingerbreadMan(0)->getName(), "Middle");
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, GetGingerbreadManRejectInvalidIndex) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(front));

    EXPECT_THROW(group.getGingerbreadMan(-1), std::out_of_range);
    EXPECT_THROW(group.getGingerbreadMan(1), std::out_of_range);
}

TEST(GingerbreadGroupTest, GetGingerbreadMan) {
    GingerbreadGroup group(3);
    GingerbreadMan front("Front", Element::Fire, Position::Front, 100, 10, 100, 0.5, 3, 5);
    group.addGingerbreadMan(std::make_shared<GingerbreadMan>(front));

    std::shared_ptr<GingerbreadMan> actual = group.getGingerbreadMan(0);
    EXPECT_EQ(actual->getName(), "Front");
    EXPECT_EQ(actual->getElementType(), Element::Fire);
    EXPECT_EQ(actual->getPosition(), Position::Front);
    EXPECT_EQ(actual->getDamage(), 100);
    EXPECT_EQ(actual->getDefense(), 10);
    EXPECT_EQ(actual->getHealth(), 100);
}