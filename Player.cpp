#include "Player.h"
#include "Room.h"


Player::Player(string n, int h, int a, int d): GameCharacter(n, h, a, d) {
        // first item
        Item dagger = Item("Dagger", 0, 5, 0);
        addItem(dagger);

        name = n;
        maxHealth = h;
        currentHealth = h;
        attack = a;
        defense = d;
}

void Player::addItem(Item i) {
    inventory.push_back(i);
    increaseStats(i.health, i.attack, i.defense);
}

void Player::increaseStats(int h, int a, int d) {
    currentHealth += h;
    maxHealth += h;
    attack += a;
    defense += d;
}

void Player::lootRoom(Room * r) {
    // Accessing a pointer uses ->
    vector<Item> items = r->items;
    for (int i = 0; i < items.size(); i++) {
        addItem(items[i]);
    }
}

void Player::changeRooms(Room * newRoom) {
    previousRoom = currentRoom;
    currentRoom = newRoom;
}
