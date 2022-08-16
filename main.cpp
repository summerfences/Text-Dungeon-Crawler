/*
* Dungeon Crawler RPG by Frank Passantino, 7/10/2022 v0.3
* v0.1 finished 7/8/2022
* Coded in Code::Blocks
* To implement:
* Make game logic more extensible to support a specified number of rooms
* Implement random placement of items and character
* More rooms!!!
*/
#include <iostream>
#include "Dungeon.h"
#include "Player.h"
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;


string intro();

int main() {

    string n = intro();
    Player player = Player(n, 100, 50, 40);
    GameCharacter skeleton = GameCharacter("Skeleton", 75, 60, 20);
    GameCharacter  pluto = GameCharacter("demon", 100, 75, 70);
    Item gladius = Item("Gladius", 0, 10, 0);
    Item potion = Item("strange serum.", 75, 15, 25);
    // vector groups to hand into the rooms
    vector<Item> g = {gladius};
    vector<Item> p = {potion};
    vector<GameCharacter> e1 = {skeleton};
    vector<GameCharacter> e2 = {pluto};

    // make rooms
    Dungeon dungeon = Dungeon(player);
    Room room1 = Room(0, false, vector<Item>(), vector<GameCharacter>());
    Room room2 = Room(1, false, g, vector<GameCharacter>());
    Room room3 = Room(2, false, p, e1);
    Room room4 = Room(3, true, vector<Item>(), e2);
    dungeon.rooms[0] = room1;
    dungeon.rooms[1] = room2;
    dungeon.rooms[2] = room3;
    dungeon.rooms[3] = room4;

    // game loop
    while (true) {
        int result = dungeon.runDungeon();
        if (result == 0) {
            break;
        }
    }
            cout << "Di te incolumem custodiant!\n";
}

string intro () {
    string n;
    cout << "What is your name, adventurer? ";
    // Account for spaces in names.
    getline(cin, n);
    cout << "Salve, " << n << ".\nMay Father Janus be your guide on this journey.\n";
    return n;
}
