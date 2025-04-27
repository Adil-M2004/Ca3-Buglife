#include "Crawler.h"
#include <cstdlib>

Crawler::Crawler(int id, const Position& pos, Direction dir, int size)
    : Bug(id, pos, dir, size) {
}

void Crawler::move() {
    if (!alive) return;

    // If way is blocked, choose a new random direction
    while (isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1);
    }

    // Move one step in the current direction
    switch (direction) {
        case Direction::NORTH: position.y--; break;
        case Direction::EAST: position.x++; break;
        case Direction::SOUTH: position.y++; break;
        case Direction::WEST: position.x--; break;
    }

    // Add new position to path
    path.push_back(position);
}

Bug* Crawler::clone() const {
    return new Crawler(*this);
}
