#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
private:
    std::string name;
    int health;
    int maxHealth;
    int damage;
    int level;
    int experience;
    int healthPotions;

public:
    Player(std::string name);

    std::string getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getDamage() const;
    int getLevel() const;
    int getExperience() const;
    int getHealthPotions() const;

    void takeDamage(int amount);
    void heal(int amount);
    void addExperience(int amount);

    bool useHealthPotion();
    bool isAlive() const;
};

#endif
