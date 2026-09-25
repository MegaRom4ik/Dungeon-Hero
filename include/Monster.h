 #ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster
{
private:
    std::string name;
    int health;
    int damage;
    int experienceReward;

public:
    Monster(std::string name, int health, int damage, int experienceReward);

    std::string getName() const;
    int getHealth() const;
    int getDamage() const;
    int getExperienceReward() const;

    void takeDamage(int amount);
    bool isAlive() const;
};

#endif