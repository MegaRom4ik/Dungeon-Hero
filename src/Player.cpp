#include "../include/Player.h"

Player::Player(std::string name)
{
    this->name = name;

    maxHealth = 100;
    health = maxHealth;

    damage = 10;
    level = 1;
    experience = 0;

    healthPotions = 3;
}

std::string Player::getName() const
{
    return name;
}

int Player::getHealth() const
{
    return health;
}

int Player::getMaxHealth() const
{
    return maxHealth;
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

int Player::getHealthPotions() const
{
    return healthPotions;
}

void Player::takeDamage(int amount)
{
    health -= amount;

    if (health < 0)
    {
        health = 0;
    }
}

void Player::heal(int amount)
{
    health += amount;

    if (health > maxHealth)
    {
        health = maxHealth;
    }
}

void Player::addExperience(int amount)
{
    experience += amount;

    while (experience >= 100)
    {
        experience -= 100;

        level++;

        maxHealth += 20;
        health += 20;

        damage += 5;
    }
}

bool Player::useHealthPotion()
{
    if (healthPotions <= 0)
    {
        return false;
    }

    if (health >= maxHealth)
    {
        return false;
    }

    healthPotions--;

    heal(40);

    return true;
}

bool Player::isAlive() const
{
    return health > 0;
}
