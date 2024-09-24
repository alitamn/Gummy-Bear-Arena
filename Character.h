#pragma once
#include <string>
#include <iostream>

// Base class for characters in the game

class Character {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    // Constructor
    Character(std::string name, int health = 0, int attack = 0, int defense = 0);

    // Virtual destructor
    virtual ~Character() {}

    // Getter and setter methods for name
    std::string getName() const;
    void setName(std::string name);

    // Getter and setter methods for attack
    int getAttack() const;
    void setAttack(int newAttack);

    // Getter and setter methods for defense
    int getDefense() const;
    void setDefense(int newDefense);

    // Getter and setter methods for health
    int getHealth() const;
    void setHealth(int newHealth);

    void ClampHealth();

    // Abstract methods to be implemented by derived classes
    virtual void Attack() = 0;
    virtual void Train() = 0;
    virtual void Defend() = 0;
    virtual void TakeDamage(int damage) = 0;
    virtual void SaveFile(std::string fileName, std::string name, int health, int attack, int defense, std::string typeString) const = 0;

    void displayStats() const;
};


// Constructor definition
Character::Character(std::string name, int health, int attack, int defense)
    : name(name), health(health), attack(attack), defense(defense) {}


std::string Character::getName() const {
    return name;
}

void Character::setName(std::string name) {
    this->name = name;
}

int Character::getAttack() const {
    return attack;
}

void Character::setAttack(int newAttack) {
    attack = newAttack;
}

int Character::getDefense() const {
    return defense;
}

void Character::setDefense(int newDefense) {
    defense = newDefense;
}

int Character::getHealth() const {
    return health;
}

void Character::setHealth(int newHealth) {
    health = newHealth;
}

// Clamp health to ensure it's within valid range
void Character::ClampHealth() {
    if (health > 100) {
        health = 100;
    }
}

// Display character's stats
void Character::displayStats() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Attack: " << attack << std::endl;
    std::cout << "Defense: " << defense << std::endl;
}