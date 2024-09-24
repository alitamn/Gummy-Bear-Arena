#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "GummyBear.h"
#include "CustomOpponent.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
    string playerName;
    int gummyBearType, opponentType;
    int roundNumber = 1;
    cout << "------------------------------------------" << endl;
    cout << "------------------------------------------" << endl;

    cout << endl;
    cout << endl;
    cout << "           GUMMY BEAR ARENA           " << endl;
    cout << endl;
    cout << endl;
    cout << "------------------------------------------" << endl;
    cout << "------------------------------------------" << endl;
    cout << endl;
    cout << endl;
    cout << "Welcome to the Gummy Bear Arena!" << endl;
    cout << "1. Start a new game" << endl;
    cout << "2. Load a saved game" << endl;
    cout << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        // Start a new game
        cout << "Enter your character's name: ";
        cin.ignore(); 
        getline(cin, playerName);

        cout << endl;
        cout << "Please select your Gummy Bear type: " << endl;
        cout << "--------------------------" << endl;
        cout << "1: Fruity Blast Bear" << endl;
        cout << "2: Chocolate Chunk Bear" << endl;
        cout << "3: Honey Hive Bear" << endl;
        cout << "Enter an option: ";
        cin >> gummyBearType;

        cout << endl;
        cout << endl;
        cout << "Select your opponent" << endl;
        cout << "--------------------------" << endl;
        cout << "1: Sour Sentinel" << endl;
        cout << "2: Gummy Goliath" << endl;
        cout << "3: Jelly Jester" << endl;
        cout << "Enter an option: ";
        cin >> opponentType;

        // Create player and opponent objects
        GummyBear player(playerName, gummyBearType);
        CustomOpponent opponent(opponentType);
        player.setOpponent(&opponent);

        // Game loop 
        while (player.getHealth() > 0 && opponent.health > 0) {
            // Display player and opponent information
            cout << endl;
            player.displayAsciiArt();
            player.displayStats();
            cout << endl;
            cout << "Opponent: " << opponent.name << endl;
            cout << "Health: " << opponent.health << endl;

            int choice;
            cout << endl;
            
            // Perform selected action
            cout << "Choose an action" << endl;
            cout << "1: Attack" << endl;
            cout << "2: Train" << endl;
            cout << "3: Defend" << endl;
            cout << "4: Save Game" << endl;
            cin >> choice;

            switch (choice) {
                case 1:
                    player.Attack();
                    break;
                case 2:
                    player.Train();
                    break;
                case 3:
                    player.Defend();
                    break;
                case 4:
                    // Save game state
                    player.SaveFile("userinfo", player.getName(), player.getHealth(), player.getAttack(), player.getDefense(), player.getTypeString());
                    opponent.SaveFile("userinfo");
                    cout << "------------------------------------------" << endl;
                    cout << "Game saved. Exiting..." << endl;
                    return 0; // Exit the game after saving
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }
            
            // Opponent's turn
            opponent.PerformAction(player);

            cout << "Round " << roundNumber++ << " completed." << endl;
            cout << "---------------------" << endl;
            cout << endl;
        }

        // Determine game outcome
        if (player.getHealth() <= 0) {
            cout << "Game Over! You have been defeated." << endl;
        } else if (opponent.health <= 0) {
            cout << "Congratulations! You have defeated " << opponent.name << "." << endl;
        } else {
            // Game is not over yet, both player and opponent have health remaining
            cout << "Game state loaded. Continue playing." << endl;
        }
    } else if (choice == 2) {
        // Load a saved game
        ifstream playerFile("userinfo.txt");
        if (!playerFile.is_open()) {
            cerr << "Unable to open userinfo.txt" << endl;
            return 1; 
        }

        string line;
        string playerName, typeString;
        int health, attack, defense, gummyBearType;

        // Read player information from file
        getline(playerFile, playerName); 
        getline(playerFile, line); 
        health = stoi(line.substr(line.find(":") + 1));
        getline(playerFile, line); 
        attack = stoi(line.substr(line.find(":") + 1));
        getline(playerFile, line); 
        defense = stoi(line.substr(line.find(":") + 1));
        getline(playerFile, typeString); 

        // Split the line using the colon as a delimiter
        size_t colonPos = typeString.find(":");
        if (colonPos != std::string::npos) {
            typeString = typeString.substr(colonPos + 1); 
            typeString.erase(0, typeString.find_first_not_of(" ")); 
            typeString.erase(typeString.find_last_not_of(" ") + 1); 
        }

        // Convert the type string to an integer
        if (typeString == "Fruity Blast Bear") {
            gummyBearType = 1;
        } else if (typeString == "Chocolate Chunk Bear") {
            gummyBearType = 2;
        } else if (typeString == "Honey Hive Bear") {
            gummyBearType = 3;
        } else {
            cerr << "Invalid gummy bear type: " << typeString << endl;
            return 1; 
        }

        // Create player object
        GummyBear player(playerName, gummyBearType, health, attack, defense);

        // Load opponent data from file
        ifstream opponentFile("userinfo_opponent.txt");
        if (opponentFile.is_open()) {
            string line;
            string opponentName;
            int opponentHealth, opponentAttack, opponentDefense, opponentType;

            // Read opponent information from file
            if (getline(opponentFile, line) && line.find("Name: ") == 0) {
                opponentName = line.substr(6); 

                // Convert the opponent name to a number
                if (opponentName == "Sour Sentinel") {
                    opponentType = 1;
                } else if (opponentName == "Gummy Goliath") {
                    opponentType = 2;
                } else if (opponentName == "Jelly Jester") {
                    opponentType = 3;
                } else {
                    cerr << "Invalid opponent name: " << opponentName << endl;
                    opponentFile.close();
                    return 1; 
                }
            } else {
                cerr << "Invalid file format: Expected 'Name: ' line" << endl;
                opponentFile.close();
                return 1; 
            }
            
            // Read opponent stats
            if (getline(opponentFile, line)) 
                opponentHealth = stoi(line.substr(line.find(":") + 1));
            else {
                cerr << "Invalid file format: Expected 'Health: ' line" << endl;
                opponentFile.close();
                return 1;
            }
            
            if (getline(opponentFile, line)) 
                opponentAttack = stoi(line.substr(line.find(":") + 1));
            else {
                cerr << "Invalid file format: Expected 'Attack: ' line" << endl;
                opponentFile.close();
                return 1;
            }
            
            if (getline(opponentFile, line)) 
                opponentDefense = stoi(line.substr(line.find(":") + 1));
            else {
                cerr << "Invalid file format: Expected 'Defense: ' line" << endl;
                opponentFile.close();
                return 1;
            }
            
            opponentFile.close();
            
            // Create the CustomOpponent object and assign it to the player
            CustomOpponent opponent(opponentType, opponentHealth, opponentAttack, opponentDefense);
            player.setOpponent(&opponent);
            
            // Game Loop
            while (player.getHealth() > 0 && opponent.health > 0) {
                cout << endl;
                player.displayAsciiArt();
                player.displayStats();
                cout << endl;
                cout << "Opponent: " << opponent.name << endl;
                cout << "Health: " << opponent.health << endl;
            
                int choice;
                cout << endl;
                cout << "Choose an action" << endl;
                cout << "1: Attack" << endl;
                cout << "2: Train" << endl;
                cout << "3: Defend" << endl;
                cout << "4: Save Game" << endl;
                cin >> choice;
            
                switch (choice) {
                    case 1:
                        player.Attack();
                        break;
                    case 2:
                        player.Train();
                        break;
                    case 3:
                        player.Defend();
                        break;
                    case 4:
                        player.SaveFile("userinfo", player.getName(), player.getHealth(), player.getAttack(), player.getDefense(), player.getTypeString());
                        opponent.SaveFile("userinfo");
                        cout << "Game saved. Exiting..." << endl;
                        return 0; // Exit the game after saving
                    default:
                        cout << "Invalid choice!" << endl;
                        break;
                }
            
                opponent.PerformAction(player);
            
                cout << "Round " << roundNumber++ << " completed." << endl;
                cout << "---------------------" << endl;
                cout << endl;
            }

            // Determine game outcome
            if (player.getHealth() <= 0) {
                cout << "Game Over! You have been defeated." << endl;
            } else {
                cout << "Congratulations! You have defeated " << opponent.name << "." << endl;
            }
            } else {
                cerr << "Unable to open opponent file" << endl;
            }
            } else {
                cerr << "Unable to open player file" << endl;
            }
            
            return 0;
            }
