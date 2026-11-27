#include <gtest/gtest.h>
#include "Battle.h"
#include <sstream>
#include <iostream>

// Вспомогательный класс для перехвата потоков ввода и вывода std::cin / std::cout
// Позволяет полностью тестировать пошаговый бой без изменения исходного кода игры
class CinCoutRedirector {
private:
    std::streambuf* origCin;
    std::streambuf* origCout;
    std::istringstream in;
    std::ostringstream out;

public:
    explicit CinCoutRedirector(const std::string& input)
        : origCin(std::cin.rdbuf()),
          origCout(std::cout.rdbuf()),
          in(input)
    {
        std::cin.rdbuf(in.rdbuf());
        std::cout.rdbuf(out.rdbuf());
    }

    ~CinCoutRedirector() {
        std::cin.rdbuf(origCin);
        std::cout.rdbuf(origCout);
    }

    std::string getOutput() const {
        return out.str();
    }
};

// Тест: игрок атакует и побеждает монстра
TEST(BattleTest, PlayerAttacksAndDefeatsMonster) {
    Player player("Hero");          // 100 HP, 10 урона
    Monster goblin("Goblin", 15, 5, 25); // 15 HP, 5 урона, 25 опыта

    // 2 атаки (1, 1):
    // 1 ход: игрок наносит 10 урона (у гоблина 5 HP), гоблин наносит 5 урона (у игрока 95 HP)
    // 2 ход: игрок наносит 10 урона (гоблин погибает, бой завершается)
    CinCoutRedirector redirector("1\n1\n");

    Battle battle;
    battle.start(player, goblin);

    EXPECT_FALSE(goblin.isAlive());
    EXPECT_EQ(goblin.getHealth(), 0);
    EXPECT_TRUE(player.isAlive());
    EXPECT_EQ(player.getHealth(), 95);
    EXPECT_EQ(player.getExperience(), 25);

    std::string output = redirector.getOutput();
    EXPECT_NE(output.find("Goblin побежден!"), std::string::npos);
    EXPECT_NE(output.find("Получено опыта: 25"), std::string::npos);
}

// Тест: игрок выбирает сбежать из боя (действие 3)
TEST(BattleTest, PlayerFleesFromBattle) {
    Player player("Hero");
    Monster orc("Orc", 100, 10, 50);

    CinCoutRedirector redirector("3\n");

    Battle battle;
    battle.start(player, orc);

    EXPECT_TRUE(player.isAlive());
    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_TRUE(orc.isAlive());
    EXPECT_EQ(orc.getHealth(), 100);

    std::string output = redirector.getOutput();
    EXPECT_NE(output.find("Hero сбежал из боя!"), std::string::npos);
}

// Тест: просмотр характеристик (действие 2) не тратит ход на атаку монстра
TEST(BattleTest, PlayerViewsStatsThenFlees) {
    Player player("Hero");
    Monster goblin("Goblin", 50, 5, 20);

    // Действие 2 (статы), затем действие 3 (побег)
    CinCoutRedirector redirector("2\n3\n");

    Battle battle;
    battle.start(player, goblin);

    EXPECT_EQ(player.getHealth(), 100); // Монстр не атаковал при просмотре статов
    EXPECT_TRUE(goblin.isAlive());

    std::string output = redirector.getOutput();
    EXPECT_NE(output.find("Герой"), std::string::npos);
    EXPECT_NE(output.find("Имя: Hero"), std::string::npos);
    EXPECT_NE(output.find("HP: 100 / 100"), std::string::npos);
}

// Тест: использование зелья в бою (действие 4)
TEST(BattleTest, PlayerUsesPotionDuringBattle) {
    Player player("Hero");
    player.takeDamage(50); // HP = 50, зелий 3
    Monster goblin("Goblin", 10, 5, 20); // 10 HP, погибает от 1 удара

    // 1 ход: действие 4 (зелье): лечит 40 HP (стало 90), монстр бьет на 5 (стало 85)
    // 2 ход: действие 1 (атака): игрок наносит 10 урона и убивает гоблина
    CinCoutRedirector redirector("4\n1\n");

    Battle battle;
    battle.start(player, goblin);

    EXPECT_EQ(player.getHealthPotions(), 2);
    EXPECT_EQ(player.getHealth(), 85);
    EXPECT_FALSE(goblin.isAlive());

    std::string output = redirector.getOutput();
    EXPECT_NE(output.find("использует лечебное зелье!"), std::string::npos);
    EXPECT_NE(output.find("Восстановлено HP: 40"), std::string::npos);
}

// Тест: попытка использовать зелье при полном здоровье сообщает об ошибке и не тратит ход
TEST(BattleTest, PlayerUsesPotionAtFullHealth) {
    Player player("Hero"); // 100/100 HP
    Monster skeleton("Skeleton", 70, 7, 30);

    // Действие 4 (зелье при полном HP), затем 3 (побег)
    CinCoutRedirector redirector("4\n3\n");

    Battle battle;
    battle.start(player, skeleton);

    EXPECT_EQ(player.getHealthPotions(), 3);
    EXPECT_EQ(player.getHealth(), 100); // Скелет не атаковал

    std::string output = redirector.getOutput();
    EXPECT_NE(output.find("У героя уже полное здоровье!"), std::string::npos);
}

// Тест: попытка использовать зелье, когда их 0
TEST(BattleTest, PlayerUsesPotionWhenEmpty) {
    Player player("Hero");
    player.takeDamage(90);
    // Тратим 3 зелья до боя
    player.useHealthPotion();
    player.useHealthPotion();
    player.useHealthPotion();
    EXPECT_EQ(player.getHealthPotions(), 0);

    player.takeDamage(20); // HP < max, но зелий 0
    int hpBefore = player.getHealth();

    Monster skeleton("Skeleton", 70, 7, 30);

    // Действие 4 (зелье, когда их 0), затем 3 (побег)
    CinCoutRedirector redirector("4\n3\n");

    Battle battle;
    battle.start(player, skeleton);

    EXPECT_EQ(player.getHealth(), hpBefore); // Ход не засчитан монстру

    std::string output = redirector.getOutput();
    EXPECT_NE(output.find("Зелья закончились!"), std::string::npos);
}

// Тест: неверный ввод обрабатывается корректно (действие по умолчанию)
TEST(BattleTest, InvalidChoiceHandled) {
    Player player("Hero");
    Monster goblin("Goblin", 50, 5, 20);

    // Вводим неверный пункт 99, затем 3 (побег)
    CinCoutRedirector redirector("99\n3\n");

    Battle battle;
    battle.start(player, goblin);

    EXPECT_EQ(player.getHealth(), 100);

    std::string output = redirector.getOutput();
    EXPECT_NE(output.find("Неверный выбор!"), std::string::npos);
}

// Тест: монстр побеждает героя в бою
TEST(BattleTest, MonsterDefeatsPlayer) {
    Player player("Hero");
    player.takeDamage(95); // Осталось всего 5 HP
    Monster orc("Orc", 100, 10, 50); // Урон орка 10 > 5 HP героя

    // Атака игрока (1): орк получает 10 урона, затем атакует на 10 и убивает героя
    CinCoutRedirector redirector("1\n");

    Battle battle;
    battle.start(player, orc);

    EXPECT_FALSE(player.isAlive());
    EXPECT_EQ(player.getHealth(), 0);

    std::string output = redirector.getOutput();
    EXPECT_NE(output.find("Hero погиб!"), std::string::npos);
}
