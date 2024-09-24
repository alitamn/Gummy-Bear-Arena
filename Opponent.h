#pragma once
#include <string>

class Character; // Forward declaration of the Character class

class Opponent {
public:
    std::string name;
    int health;
    int attack;
    int defense;

    Opponent() {} 
    virtual ~Opponent() {}

    // Pure virtual function to perform an action by the opponent
    virtual void PerformAction(Character& player) = 0;

    // Pure virtual function to save opponent data to a file
    virtual void SaveFile(std::string fileName) const = 0;

    
};