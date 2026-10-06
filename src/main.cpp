#include "../include/Player.h"
#include "../include/Monster.h"
#include "../include/Battle.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(std::time(nullptr));

    Player player("Hero");
    Battle battle;

    int battleNumber = 1;

    while (player.isAlive())
    {
             std::cout << "          БОЙ №" << battleNumber << std::endl;
     
        int randomMonster = std::rand() % 3;

        Monster monster("Goblin", 50, 5, 20);

        if (randomMonster == 0)
        {
            monster = Monster("Goblin", 50, 5, 20);
        }
        else if (randomMonster == 1)
        {
            monster = Monster("Skeleton", 70, 7, 30);
        }
        else
        {
            monster = Monster("Orc", 100, 10, 50);
        }

        std::cout << "\nПоявился противник: "
                  << monster.getName() << "!" << std::endl;

        std::cout << "HP противника: "
                  << monster.getHealth() << std::endl;

        std::cout << "Урон противника: "
                  << monster.getDamage() << std::endl;

        std::cout << "\nHP героя: "
                  << player.getHealth()
                  << " / "
                  << player.getMaxHealth()
                  << std::endl;

        int oldLevel = player.getLevel();

        battle.start(player, monster);

        if (!player.isAlive())
        {
                   std::cout << "        ГЕРОЙ ПОГИБ" << std::endl;

            std::cout << "Пройдено боёв: "
                      << battleNumber - 1 << std::endl;

            break;
        }

        if (player.getLevel() > oldLevel)
        {
                   std::cout << "       НОВЫЙ УРОВЕНЬ!" << std::endl;
         
            std::cout << "Уровень: "
                      << player.getLevel() << std::endl;

            std::cout << "Максимальное HP: "
                      << player.getMaxHealth() << std::endl;

            std::cout << "Урон: "
                      << player.getDamage() << std::endl;
        }

        std::cout << "\nГерой отдыхает после боя..." << std::endl;

        int healthBeforeHealing = player.getHealth();

        player.heal(30);

        int healed = player.getHealth() - healthBeforeHealing;

        std::cout << "Восстановлено HP: "
                  << healed << std::endl;

        std::cout << "\n--- Характеристики героя ---" << std::endl;

        std::cout << "Уровень: "
                  << player.getLevel() << std::endl;

        std::cout << "HP: "
                  << player.getHealth()
                  << " / "
                  << player.getMaxHealth()
                  << std::endl;

        std::cout << "Урон: "
                  << player.getDamage() << std::endl;

        std::cout << "Опыт: "
                  << player.getExperience()
                  << " / 100" << std::endl;

        battleNumber++;

        std::cout << "\nНажмите Enter для следующего боя...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}
