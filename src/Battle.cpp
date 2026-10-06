#include "../include/Battle.h"
#include <iostream>

void Battle::start(Player& player, Monster& monster)
{
    std::cout << "Начинается бой: "
              << player.getName()
              << " против "
              << monster.getName()
              << "!" << std::endl;

    while (player.isAlive() && monster.isAlive())
    {
        int choice;

        std::cout << "\nВаш ход:" << std::endl;
        std::cout << "1. Атаковать" << std::endl;
        std::cout << "2. Посмотреть характеристики" << std::endl;
        std::cout << "3. Сбежать" << std::endl;
        std::cout << "4. Использовать зелье ("
                  << player.getHealthPotions()
                  << ")" << std::endl;

        std::cout << "Выберите действие: ";

        std::cin >> choice;

        if (choice == 1)
        {
            monster.takeDamage(player.getDamage());

            std::cout << player.getName()
                      << " атакует "
                      << monster.getName()
                      << "!" << std::endl;

            std::cout << "HP монстра: "
                      << monster.getHealth()
                      << std::endl;
        }
        else if (choice == 2)
        {
            std::cout << "\n Герой " << std::endl;

            std::cout << "Имя: "
                      << player.getName()
                      << std::endl;

            std::cout << "HP: "
                      << player.getHealth()
                      << " / "
                      << player.getMaxHealth()
                      << std::endl;

            std::cout << "Урон: "
                      << player.getDamage()
                      << std::endl;

            std::cout << "Уровень: "
                      << player.getLevel()
                      << std::endl;

            std::cout << "Опыт: "
                      << player.getExperience()
                      << " / 100"
                      << std::endl;

            std::cout << "Зелья: "
                      << player.getHealthPotions()
                      << std::endl;

            continue;
        }
        else if (choice == 3)
        {
            std::cout << player.getName()
                      << " сбежал из боя!"
                      << std::endl;

            break;
        }
        else if (choice == 4)
        {
            int oldHealth = player.getHealth();

            if (player.useHealthPotion())
            {
                int healed =
                    player.getHealth() - oldHealth;

                std::cout << player.getName()
                          << " использует лечебное зелье!"
                          << std::endl;

                std::cout << "Восстановлено HP: "
                          << healed
                          << std::endl;

                std::cout << "HP героя: "
                          << player.getHealth()
                          << " / "
                          << player.getMaxHealth()
                          << std::endl;

                std::cout << "Осталось зелий: "
                          << player.getHealthPotions()
                          << std::endl;
            }
            else
            {
                if (player.getHealthPotions() <= 0)
                {
                    std::cout << "Зелья закончились!"
                              << std::endl;
                }
                else
                {
                    std::cout << "У героя уже полное здоровье!"
                              << std::endl;
                }

                continue;
            }
        }
        else
        {
            std::cout << "Неверный выбор!"
                      << std::endl;

            continue;
        }

        if (!monster.isAlive())
        {
            std::cout << monster.getName()
                      << " побежден!"
                      << std::endl;

            player.addExperience(
                monster.getExperienceReward()
            );

            std::cout << "Получено опыта: "
                      << monster.getExperienceReward()
                      << std::endl;

            break;
        }

        player.takeDamage(monster.getDamage());

        std::cout << monster.getName()
                  << " атакует!"
                  << std::endl;

        std::cout << "HP героя: "
                  << player.getHealth()
                  << " / "
                  << player.getMaxHealth()
                  << std::endl;
    }

    if (!player.isAlive())
    {
        std::cout << player.getName()
                  << " погиб!"
                  << std::endl;
    }
}
