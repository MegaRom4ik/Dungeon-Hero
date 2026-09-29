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
        monster.takeDamage(player.getDamage());

        std::cout << player.getName()
                  << " атакует. HP монстра: "
                  << monster.getHealth()
                  << std::endl;

        if (!monster.isAlive())
        {
            std::cout << monster.getName()
                      << " побежден!" << std::endl;

            player.addExperience(monster.getExperienceReward());
            break;
        }

        player.takeDamage(monster.getDamage());

        std::cout << monster.getName()
                  << " атакует. HP героя: "
                  << player.getHealth()
                  << std::endl;
    }
}
