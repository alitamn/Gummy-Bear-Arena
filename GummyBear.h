#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Character.h"
#include "Opponent.h"

// GummyBear class derived from Character
class GummyBear : public Character {
private:
    int type;  // Type of gummy bear
    Opponent* opponent; // Pointer to opponent object
    bool opponentDefended;
    bool easterEggUnlocked;

    void updateOpponentHealth(int damageTaken);

public:
   // Constructor
   GummyBear(std::string name, int type, int health = 100, int attack = 50, int defense = 30);

    // Destructor
    virtual ~GummyBear() {}

    // Override methods from base class Character
    void Attack() override;
    void Train() override;
    void Defend() override;
    void TakeDamage(int damage) override;

    void displayAsciiArt();

    int getAttack() const;
    int getDefense() const;
    std::string getTypeString() const;

void SaveFile(std::string fileName, std::string name, int health, int attack, int defense, std::string typeString) const override;

    bool getOpponentDefended() const;
    void setOpponent(Opponent* opponent);

private:
    // Private method to check and trigger easter egg abilities
    void checkEasterEgg();
};


void GummyBear::updateOpponentHealth(int damageTaken) {
    opponent->health -= damageTaken;
}

GummyBear::GummyBear(std::string name, int type, int health, int attack, int defense)
: Character(name, health, attack, defense), type(type), opponent(nullptr), opponentDefended(false), easterEggUnlocked(false) {
    if (health == 0 && attack == 0 && defense == 0) {
        // If no values are provided, use the default values based on the type
        switch (type) {
            case 1: // Fruity Blast Bear
                health = 100;
                attack = 50;
                defense = 30;
                break;
            case 2: // Chocolate Chunk Bear
                health = 120;
                attack = 40;
                defense = 60;
                break;
            case 3: // Honey Hive Bear
                health = 150;
                attack = 30;
                defense = 40;
                break;
            default:
                std::cout << "Invalid gummy bear type!" << std::endl;
                break;
        }
    }

    ClampHealth();
    // Print characteristics based on gummy bear type
    switch (type) {
        case 1: // Fruity Blast Bear
            std::cout << std::endl;
            std::cout << "Your gummy bear is infused with the power of " << std::endl;
            std::cout << "fruits, giving it agility and quick reflexes." << std::endl;
            std::cout << std::endl;
            break;
        
        case 2: // Chocolate Chunk Bear
            std::cout << std::endl;
            std::cout << "Your gummy bear is made of rich chocolate," << std::endl;
            std::cout << "providing it with strong defensive capabilities." << std::endl;
            std::cout << std::endl;
            break;
        
        case 3: // Honey Hive Bear
            std::cout << std::endl;
            std::cout << "Your gummy bear harnesses the sweetness of honey," << std::endl;
            std::cout << "granting it healing powers and resilience." << std::endl;
            std::cout << std::endl;
            break;
        default:
            std::cout << "Invalid gummy bear type!" << std::endl;
            break;
    }

    // Set gummy bear attributes
    this->health = health;
    this->attack = attack;
    this->defense = defense;
}


// Method to perform attack action
void GummyBear::Attack() {
    std::cout << name << " attacks!" << std::endl;
    int damageTaken = attack - opponent->defense;
    if (damageTaken > 0) {
        updateOpponentHealth(damageTaken);
    }

    opponentDefended = false;
    checkEasterEgg();
}

// Method to perform train action
void GummyBear::Train() {
    std::cout << name << " trains!" << std::endl;
    int attackIncrease = 10;
    int defenseIncrease = 5;

    // Check if the increased values exceed the maximum allowed
    if (attack + attackIncrease > 100) {
        attackIncrease = 100 - attack;
    }
    if (defense + defenseIncrease > 100) {
        defenseIncrease = 100 - defense;
    }

    attack += attackIncrease;
    defense += defenseIncrease;

    std::cout << "Attack increased by " << attackIncrease << "!" << std::endl;
    std::cout << "Defense increased by " << defenseIncrease << "!" << std::endl;
}


// Method to perform defend action
void GummyBear::Defend() {
    std::cout << name << " defends!" << std::endl;
        opponentDefended = true;
        defense += 5;
    

}

// Method to take damage from opponent
void GummyBear::TakeDamage(int damage) {
    int damageTaken = damage - defense;
    if (damageTaken > 0) {
        health -= damageTaken;
        std::cout << name << " took " << damageTaken << " damage!" << std::endl;
    } else {
        std::cout << name << "'s defense blocked the attack!" << std::endl;
    }
}

void GummyBear::displayAsciiArt() {
    switch (type) {
    case 1: // Fruity Blast Bear (Art by Herman Hiddema)
        std::cout << R"(
             {"`-'"}
              (o o)
            ,--`Y'--.
            `-:,-.;-'
              /`_'\  
             (_/ \_)   
        )" << std::endl;
        break;
    case 2: // Chocolate Chunk Bear (Art by R. Elizabeth A)
        std::cout << R"(
               /\___/\
               | o o |
              __\_^_/__
             (__/   \__)
              _|  .  |_
             (__\___/__)
        )" << std::endl;
        break;
    case 3: // Honey Hive Bear (Art by Rick Cox)
        std::cout << R"(
               ( )_____( )
                / O   O \
               |   (@)   |
               \    ~    /  
                \ <}*{> /   
             ___/  ___  \___
            ()___ /   \ ___()
                ( \___/ )
               /_ /   \ _\
              (__)     (__)
        )" << std::endl;
        break;
    default:
        break;
    }
}
// Method to save gummy bear information to file
    void GummyBear::SaveFile(std::string fileName, std::string name, int health, int attack, int defense, std::string typeString) const {
        std::ofstream outputFile(fileName + ".txt"); 

        if (outputFile.is_open()) {
            outputFile << "Name: " << name << std::endl;
            outputFile << "Health: " << health << std::endl;
            outputFile << "Attack: " << attack << std::endl;
            outputFile << "Defense: " << defense << std::endl;
            outputFile << "Type: " << typeString << std::endl;

            std::cout << "Player information saved to " << fileName << ".txt" << std::endl;
        } else {
            std::cerr << "Unable to open file " << fileName << ".txt" << std::endl;
        }

        outputFile.close(); // Close the file
    }

   

void GummyBear::checkEasterEgg() {
    switch (type) {
            case 1: // Fruity Blast Bear
                if (!easterEggUnlocked && opponent->health < 20) {
                    std::cout << "Fruity Blast Bear drops a fruit bomb, granting an automatic win!" << std::endl;
                    easterEggUnlocked = true;
                    opponent->health = 0; // Set opponent's health to 0 for an automatic win
                }
                break;
            case 2: // Chocolate Chunk Bear
                if (!easterEggUnlocked && health < 30) {
                    std::cout << "Chocolate Chunk Bear enters a chocolate frenzy mode!" << std::endl;
                    easterEggUnlocked = true;
                    attack *= 2; // Double the attack power
                    defense = health; // Set defense equal to current health for temporary invincibility
                }
                break;
            case 3: // Honey Hive Bear
                if (!easterEggUnlocked && health < 20) {
                    std::cout << "Honey Hive Bear summons friendly bees!" << std::endl;
                    easterEggUnlocked = true;
                    health += 50;
                    ClampHealth(); // Heal the bear by 50 health points
                }
                break;
            }
        }

// Method to get string representation of gummy bear type
std::string GummyBear::getTypeString() const {
    switch (type) {
        case 1:
            return "Fruity Blast Bear";
        case 2:
            return "Chocolate Chunk Bear";
        case 3:
            return "Honey Hive Bear";
        default:
            return "Invalid Type";
    }
}

void GummyBear::setOpponent(Opponent* opponent) {
    this->opponent = opponent;
}

int GummyBear::getAttack() const {
    return attack;
}

int GummyBear::getDefense() const {
    return defense;
}
    
