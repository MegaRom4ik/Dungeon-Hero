#include "../include/Player.h"

Player::Player(std::string name)
{
    this->name = name;
    health = 100;
    damage = 10;
    level = 1;
    experience = 0;
}

std::string Player::getName() const
{
    return name;
}

int Player::getHealth() const
{
    return health;
}

int Player::getDamage() const
{
    return damage;
}

int Player::getLevel() const
{
    return level;
}

int Player::getExperience() const
{
    return experience;
}

void Player::takeDamage(int amount)
{
    health -= amount;

    if (health < 0)
        health = 0;
}

void Player::addExperience(int amount)
{
    experience += amount;
}

bool Player::isAlive() const
{
    return health > 0;
}