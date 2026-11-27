#include <gtest/gtest.h>
#include "Monster.h"

// Тест инициализации монстра с заданными параметрами
TEST(MonsterTest, InitialState) {
    Monster goblin("Goblin", 50, 5, 20);

    EXPECT_EQ(goblin.getName(), "Goblin");
    EXPECT_EQ(goblin.getHealth(), 50);
    EXPECT_EQ(goblin.getDamage(), 5);
    EXPECT_EQ(goblin.getExperienceReward(), 20);
    EXPECT_TRUE(goblin.isAlive());
}

// Тест получения урона монстром
TEST(MonsterTest, TakeDamageNormal) {
    Monster skeleton("Skeleton", 70, 7, 30);
    skeleton.takeDamage(25);

    EXPECT_EQ(skeleton.getHealth(), 45);
    EXPECT_TRUE(skeleton.isAlive());
}

// Тест убийства монстра точным уроном
TEST(MonsterTest, TakeDamageExactDeath) {
    Monster orc("Orc", 100, 10, 50);
    orc.takeDamage(100);

    EXPECT_EQ(orc.getHealth(), 0);
    EXPECT_FALSE(orc.isAlive());
}

// Тест избыточного урона (здоровье не уходит в минус)
TEST(MonsterTest, TakeDamageOverkillClampedToZero) {
    Monster goblin("Goblin", 50, 5, 20);
    goblin.takeDamage(120);

    EXPECT_EQ(goblin.getHealth(), 0);
    EXPECT_FALSE(goblin.isAlive());
}
