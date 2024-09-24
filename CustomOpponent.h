#pragma once
#include <iostream>
#include "Opponent.h"
#include "Character.h"


// CustomOpponent class derived from Opponent
class CustomOpponent : public Opponent {
public:
    // Constructors
    CustomOpponent(std::string name, int health, int attack, int defense);
    CustomOpponent(int opponentType);
    CustomOpponent(int opponentType, int health, int attack, int defense);

    // Destructor
    virtual ~CustomOpponent() {}

    void PerformAction(Character& player) override;
    void SaveFile(std::string fileName) const override;
};


// Constructor with specified attributes
CustomOpponent::CustomOpponent(std::string name, int health, int attack, int defense)
    : Opponent() {
    this->name = name;
    this->health = health;
    this->attack = attack;
    this->defense = defense;
}

// Constructor based on opponent type
CustomOpponent::CustomOpponent(int opponentType) {
    switch (opponentType) {
    case 1:
        name = "Sour Sentinel";
        health = 80;
        attack = 60;
        defense = 40;
        break;
    case 2:
        name = "Gummy Goliath";
        health = 100;
        attack = 50;
        defense = 70;
        break;
    case 3:
        name = "Jelly Jester";
        health = 90;
        attack = 40;
        defense = 50;
        break;
    default:
        std::cout << "Invalid opponent type!" << std::endl;
        break;
    }
}

// Constructor based on opponent type with specified attributes
CustomOpponent::CustomOpponent(int opponentType, int health, int attack, int defense) {
    switch (opponentType) {
    case 1:
        name = "Sour Sentinel";
        this->health = health;
        this->attack = attack;
        this->defense = defense;
        break;
    case 2:
        name = "Gummy Goliath";
        this->health = health;
        this->attack = attack;
        this->defense = defense;
        break;
    case 3:
        name = "Jelly Jester";
        this->health = health;
        this->attack = attack;
        this->defense = defense;
        break;
    default:
        std::cout << "Invalid opponent type!" << std::endl;
        break;
    }
}

// Perform action based on random selection
void CustomOpponent::PerformAction(Character& player) {
    int actionType = rand() % 3;
    switch (actionType) {
    case 0: {
        std::cout << name << " attacks " << player.getName() << "!" << std::endl;
        player.TakeDamage(attack);
        break;
    }
    case 1: {
        std::cout << name << " defends against " << player.getName() << "!" << std::endl;
        break;
    }
    case 2: {
        std::cout << name << " trains for the next round!" << std::endl;
        break;
    }
    case 3: {
        std::cout << name << " skips to the next round." << std::endl;
        break;
    }
    }
}

// Save opponent data to file
void CustomOpponent::SaveFile(std::string fileName) const {
    std::ofstream outputFile(fileName + "_opponent.txt");
    if (outputFile.is_open()) {
        outputFile << "Name: " << name << std::endl;
        outputFile << "Health: " << health << std::endl;
        outputFile << "Attack: " << attack << std::endl;
        outputFile << "Defense: " << defense << std::endl;
        std::cout << "Opponent information saved to " << fileName << "_opponent.txt" << std::endl;
    } else {
        std::cerr << "Unable to open file " << fileName << "_opponent.txt" << std::endl;
    }
    outputFile.close();
}