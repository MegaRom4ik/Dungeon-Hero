#include <gtest/gtest.h>
#include "Player.h"

// Тест начальной инициализации характеристик героя
TEST(PlayerTest, InitialState) {
    Player player("Hero");

    EXPECT_EQ(player.getName(), "Hero");
    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_EQ(player.getMaxHealth(), 100);
    EXPECT_EQ(player.getDamage(), 10);
    EXPECT_EQ(player.getLevel(), 1);
    EXPECT_EQ(player.getExperience(), 0);
    EXPECT_EQ(player.getHealthPotions(), 3);
    EXPECT_TRUE(player.isAlive());
}

// Тест получения обычного урона
TEST(PlayerTest, TakeDamageNormal) {
    Player player("Hero");
    player.takeDamage(30);

    EXPECT_EQ(player.getHealth(), 70);
    EXPECT_TRUE(player.isAlive());
}

// Тест получения урона до нуля (смерть героя)
TEST(PlayerTest, TakeDamageExactDeath) {
    Player player("Hero");
    player.takeDamage(100);

    EXPECT_EQ(player.getHealth(), 0);
    EXPECT_FALSE(player.isAlive());
}

// Тест избыточного урона (здоровье не должно опускаться ниже 0)
TEST(PlayerTest, TakeDamageOverkillClampedToZero) {
    Player player("Hero");
    player.takeDamage(150);

    EXPECT_EQ(player.getHealth(), 0);
    EXPECT_FALSE(player.isAlive());
}

// Тест обычного восстановления здоровья
TEST(PlayerTest, HealNormal) {
    Player player("Hero");
    player.takeDamage(50);
    EXPECT_EQ(player.getHealth(), 50);

    player.heal(25);
    EXPECT_EQ(player.getHealth(), 75);
}

// Тест лечения сверх максимума (здоровье не может превысить maxHealth)
TEST(PlayerTest, HealOverflowClampedToMaxHealth) {
    Player player("Hero");
    player.takeDamage(20);
    EXPECT_EQ(player.getHealth(), 80);

    player.heal(50);
    EXPECT_EQ(player.getHealth(), 100);
}

// Тест начисления опыта без перехода на новый уровень
TEST(PlayerTest, AddExperienceNoLevelUp) {
    Player player("Hero");
    player.addExperience(60);

    EXPECT_EQ(player.getExperience(), 60);
    EXPECT_EQ(player.getLevel(), 1);
    EXPECT_EQ(player.getMaxHealth(), 100);
    EXPECT_EQ(player.getDamage(), 10);
}

// Тест перехода на следующий уровень ровно при 100 опыта
TEST(PlayerTest, LevelUpSingleExact) {
    Player player("Hero");
    player.addExperience(100);

    EXPECT_EQ(player.getLevel(), 2);
    EXPECT_EQ(player.getExperience(), 0);
    EXPECT_EQ(player.getMaxHealth(), 120);
    EXPECT_EQ(player.getHealth(), 120);
    EXPECT_EQ(player.getDamage(), 15);
}

// Тест перехода на следующий уровень с остатком опыта
TEST(PlayerTest, LevelUpWithRemainderExperience) {
    Player player("Hero");
    player.addExperience(135);

    EXPECT_EQ(player.getLevel(), 2);
    EXPECT_EQ(player.getExperience(), 35);
    EXPECT_EQ(player.getMaxHealth(), 120);
    EXPECT_EQ(player.getHealth(), 120);
    EXPECT_EQ(player.getDamage(), 15);
}

// Тест перехода сразу на несколько уровней (например, при получении 250 опыта)
TEST(PlayerTest, LevelUpMultipleLevels) {
    Player player("Hero");
    player.addExperience(250);

    EXPECT_EQ(player.getLevel(), 3);
    EXPECT_EQ(player.getExperience(), 50);
    EXPECT_EQ(player.getMaxHealth(), 140);
    EXPECT_EQ(player.getHealth(), 140);
    EXPECT_EQ(player.getDamage(), 20);
}

// Тест успешного использования лечебного зелья при неполном здоровье
TEST(PlayerTest, UseHealthPotionSuccess) {
    Player player("Hero");
    player.takeDamage(50); // HP = 50
    EXPECT_EQ(player.getHealthPotions(), 3);

    bool used = player.useHealthPotion(); // Восстанавливает 40 HP
    EXPECT_TRUE(used);
    EXPECT_EQ(player.getHealth(), 90);
    EXPECT_EQ(player.getHealthPotions(), 2);
}

// Тест: зелье не лечит выше maxHealth
TEST(PlayerTest, UseHealthPotionCappedAtMaxHealth) {
    Player player("Hero");
    player.takeDamage(20); // HP = 80
    bool used = player.useHealthPotion();

    EXPECT_TRUE(used);
    EXPECT_EQ(player.getHealth(), 100); // 80 + 40 -> ограничено 100
    EXPECT_EQ(player.getHealthPotions(), 2);
}

// Тест: нельзя использовать зелье при полном здоровье
TEST(PlayerTest, UseHealthPotionFullHealthFails) {
    Player player("Hero");
    EXPECT_EQ(player.getHealth(), player.getMaxHealth());

    bool used = player.useHealthPotion();
    EXPECT_FALSE(used);
    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_EQ(player.getHealthPotions(), 3); // Зелье не должно потратиться
}

// Тест: нельзя использовать зелье, когда они закончились
TEST(PlayerTest, UseHealthPotionEmptyInventoryFails) {
    Player player("Hero");
    player.takeDamage(95); // HP = 5

    // Тратим все 3 зелья
    EXPECT_TRUE(player.useHealthPotion()); // HP = 45, зелий 2
    EXPECT_TRUE(player.useHealthPotion()); // HP = 85, зелий 1
    player.takeDamage(30);                // HP = 55
    EXPECT_TRUE(player.useHealthPotion()); // HP = 95, зелий 0
    EXPECT_EQ(player.getHealthPotions(), 0);

    // Пытаемся использовать 4-е зелье при пустом инвентаре
    bool used = player.useHealthPotion();
    EXPECT_FALSE(used);
    EXPECT_EQ(player.getHealth(), 95);
    EXPECT_EQ(player.getHealthPotions(), 0);
}
