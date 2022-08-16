#include "Dungeon.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;


// constructor
Dungeon::Dungeon (Player p) {
    player = p;
}

void Dungeon::handleFightActions(GameCharacter * enemy) {
    while(true) {
        string actions[] = {"a. Attack. ", "b. Retreat."};
        printActions(2, actions);
        string input;
        cin >> input;
        // handle player actions
        if (input == "a") {
            int damage = enemy->takeDamage(player.attack);
            cout << "\nYour attack does " << damage << "damage.\n";
        }
        else if (input == "b") {
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        } else {
            cout << "Incorrect choice.\n";
        }
        // handle enemy actions
        if(enemy->checkIsDead()) {
            cout << "\nYou have defeated the enemy " << enemy->name << "!";
            player.increaseStats(10,5,5);
            player.currentRoom->clearEnemies();
            return;
        } else {
            int damage = player.takeDamage(enemy->attack);
            cout << "The " << enemy->name << "'s attack does " << damage << "damage.\n";
            cout << "Your health is now " << player.currentHealth << endl;
            if (player.checkIsDead()) {
                return;
            }
        }
    }
}

void Dungeon::handleRoomWithEnemy(Room * room) {
        GameCharacter enemy = room->enemies.front();
        cout << "\nYou enter the room, and you are greeted by a " << enemy.name << "!\n";
    string actions[] = {"a. Fight the " + enemy.name, "b. Go back to the previous room."};
    while(true) {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "a") {
            handleFightActions(&enemy);
            return;
        }
        else if (input == "b") {
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;

        } else {
            cout << "Incorrect choice.\n";
        }
    }
}

void Dungeon::handleEmptyRoom(Room * room) {
    cout << "\nYou enter the room, but it is empty.\n";
    string actions[] = {"a. Move to another room."};
    while(true) {
        printActions(1, actions);
        string input;
        cin >> input;
        if (input == "a") {
            return;
        } else {
        cout << "Incorrect choice.\n";
        }
    }
}

void Dungeon::handleLootActions(Room * room) {
    Item item = room->items.front();
    int size = room->items.size();
    player.lootRoom(room);
    room->clearLoot();
    for (int i = 0; i < size; i++) {
        cout << "\nYou open the chest and find a " + item.name << endl;
        cout << "Your health is now " << player.currentHealth << "\nYour attack is now " << player.attack << "\nYour defense is now " << player.defense << endl;

    }
}

void Dungeon::handleRoomWithChest(Room * room) {
    cout << "\nYou enter the room, and see a large chest in the middle.\n";
    string actions[] = {"a. Loot the chest.", "b. Move to another room."};
    while(true) {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "a") {
            handleLootActions(room);
            return;
        }
        else if (input == "b") {
            return;

        } else {
            cout << "Incorrect choice.\n";
        }
    }
}

void Dungeon::printActions(int numActions, string actions[]) {
    cout << "\nChoose an action:\n";
    for (int i = 0; i < numActions; i++) {
        cout << actions[i] << endl;
    }
}

void Dungeon::enterRoom(Room * room) {
    if (room->enemies.size() != 0) {
        handleRoomWithEnemy(room);
        if (room->items.size() != 0 && room->enemies.size() == 0) {
                cout << " You can now inspect the room more clearly.";
                handleRoomWithChest(room);
                return;
        }
    }
    else if (room->items.size() != 0) {
        handleRoomWithChest(room);
    }
    else {
        handleEmptyRoom(room);
    }
}

void Dungeon::handleMovementActions(Room * room) {
    while (true) {
        if (room->pos == 0) {
            string actions[] = {"a. Move right", "b. Move down"};
            printActions(2, actions);
            string input;
            cin >> input;

            if (input == "a") {
                player.changeRooms(&rooms[1]);
                return;
            }
            else if (input == "b") {
                player.changeRooms(&rooms[2]);
                return;
            } else {
                cout << "Incorrect choice.\n";
            }
        }
        else if (room->pos == 1) {
            string actions[] = {"a. Move left"};
            printActions(1, actions);
            string input;
            cin >> input;
            if (input == "a") {
                player.changeRooms(&rooms[0]);
                return;
            } else {
            cout << "Incorrect value.\n";
            }
        }
        else if (room->pos == 2) {
            string actions[] = {"a. Move up", "b. Move right"};
            printActions(2, actions);
            string input;
            cin >> input;
            if (input == "a") {
                player.changeRooms(&rooms[0]);
                return;
            }
            else if (input == "b") {
                player.changeRooms(&rooms[3]);
                return;
            } else {
                cout << "Incorrect choice.\n";
            }
        } else {
            string actions[] = {"a. Move left"};
            printActions(1, actions);
            string input;
            cin >> input;
            if (input == "a") {
                player.changeRooms(&rooms[2]);
                return;
            } else {
                cout << "Incorrect choice.\n";
            }
        }
    } // end while loop
}

int Dungeon::performEndGameLogic() {
    string actions[] = {"a. Yes", "b. No"};
    while (true) {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "a") {
            return 1;
        }
        else if (input == "b") {
            return 0;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}

int Dungeon::runDungeon() {
    cout << "\nYour journey begins with the ultimate departure, as mortality slips from your grasp.\nPassing through the nine streams of the river Styx, you have entered the underworld.\n";
    cout << "Beware, as both infinite wisdom and peril lie within these dark depths!\n\n";
    cout << "You pass through the entrance of an ominous crevice. It is the only way forward." << endl;
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];

    while(true) {
            enterRoom(player.currentRoom);
            if (player.checkIsDead()) {
                cout << "Another soul claimed to drown in the River Styx. Try again?\n";
                return performEndGameLogic();

            } else {
                if(player.currentRoom->isExit) {
                    if (player.currentRoom->enemies.size() == 0) {
                        cout << " You have conquered this crevice of the underworld, warrior!\nWould you like to play again?\n";
                        return performEndGameLogic();
                    }
                }
            }
            handleMovementActions(player.currentRoom);
    }
}
