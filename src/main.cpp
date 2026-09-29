#include "../include/Player.h"
#include "../include/Monster.h"
#include "../include/Battle.h"

#include <iostream>

int main()
{
    Player player("Hero");

    Monster monster("Goblin", 50, 5, 20);

    Battle battle;

    battle.start(player, monster);

    std::cout << "Опыт героя: "
              << player.getExperience()
              << std::endl;

    return 0;
}
