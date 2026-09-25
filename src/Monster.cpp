#include "../include/Monster.h"

Monster::Monster(std::string name, int health, int damage, int experienceReward)
{
    this->name = name;
    this->health = health;
    this->damage = damage;
    this->experienceReward = experienceReward;
}

std::string Monster::getName() const
{
    return name;
}

int Monster::getHealth() const
{
    return health;
}

int Monster::getDamage() const
{
    return damage;
}

int Monster::getExperienceReward() const
{
    return experienceReward;
}

void Monster::takeDamage(int amount)
{
    health -= amount;

    if (health < 0)
        health = 0;
}

bool Monster::isAlive() const
{
    return health > 0;
}