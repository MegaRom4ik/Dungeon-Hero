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
        std::cout << "Выберите действие: ";

        std::cin >> choice;

        if (choice == 1)
        {
            monster.takeDamage(player.getDamage());

            std::cout << player.getName()
                      << " атакует " << monster.getName()
                      << "!" << std::endl;

            std::cout << "HP монстра: "
                      << monster.getHealth()
                      << std::endl;
        }
        else if (choice == 2)
        {
            std::cout << "\nГерой: " << player.getName() << std::endl;
            std::cout << "HP: " << player.getHealth() << std::endl;
            std::cout << "Урон: " << player.getDamage() << std::endl;
            std::cout << "Уровень: " << player.getLevel() << std::endl;
            std::cout << "Опыт: " << player.getExperience() << std::endl;

            continue;
        }
        else if (choice == 3)
        {
            std::cout << player.getName()
                      << " сбежал из боя!" << std::endl;
            break;
        }
        else
        {
            std::cout << "Неверный выбор!" << std::endl;
            continue;
        }

        if (!monster.isAlive())
        {
            std::cout << monster.getName()
                      << " побежден!" << std::endl;

            player.addExperience(monster.getExperienceReward());
            break;
        }

        player.takeDamage(monster.getDamage());

        std::cout << monster.getName()
                  << " атакует!" << std::endl;

        std::cout << "HP героя: "
                  << player.getHealth()
                  << std::endl;
    }

    if (!player.isAlive())
    {
        std::cout << player.getName()
                  << " погиб!" << std::endl;
    }
}
