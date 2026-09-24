#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
private:
    std::string name;
    int health;
    int damage;
    int level;
    int experience;

public:
    Player(std::string name);

    std::string getName() const;
    int getHealth() const;
    int getDamage() const;
    int getLevel() const;
    int getExperience() const;

    void takeDamage(int amount);
    void addExperience(int amount);
    bool isAlive() const;
};

#endif