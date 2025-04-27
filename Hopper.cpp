#include "Hopper.h"
#include <cstdlib>

Hopper::Hopper(int id, const Position& pos, Direction dir, int size, int hopLength)
    : Bug(id, pos, dir, size), hopLength(hopLength) {
    // Ensure hopLength is within valid range (2-4)
    if (hopLength < 2) this->hopLength = 2;
    if (hopLength > 4) this->hopLength = 4;
}

void Hopper::move() {
    if (!alive) return;

    // If way is blocked, choose a new random direction
    while (isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1);
    }

    // Calculate target position based on hop length
    Position target = position;
    int actualHop = hopLength;
    
    // Try to hop in the current direction
    switch (direction) {
        case Direction::NORTH:
            // Check if we can hop the full length or hit the edge
            if (position.y < hopLength) {
                actualHop = position.y;
            }
            target.y -= actualHop;
            break;
            
        case Direction::EAST:
            // Check if we can hop the full length or hit the edge
            if (position.x + hopLength > 9) {
                actualHop = 9 - position.x;
            }
            target.x += actualHop;
            break;
            
        case Direction::SOUTH:
            // Check if we can hop the full length or hit the edge
            if (position.y + hopLength > 9) {
                actualHop = 9 - position.y;
            }
            target.y += actualHop;
            break;
            
        case Direction::WEST:
            // Check if we can hop the full length or hit the edge
            if (position.x < hopLength) {
                actualHop = position.x;
            }
            target.x -= actualHop;
            break;
    }
    
    // Update position to the target
    position = target;
    
    // Add new position to path
    path.push_back(position);
}

Bug* Hopper::clone() const {
    return new Hopper(*this);
}
