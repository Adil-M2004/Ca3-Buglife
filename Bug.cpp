#include "Bug.h"


Bug::Bug(int id, const Position& pos, Direction dir, int size)
    : id(id), position(pos), direction(dir), size(size), alive(true) {
    // Add initial position to path
    path.push_back(position);
}

bool Bug::isWayBlocked() const {
    // Check if bug is at the edge of the board and facing that edge
    switch (direction) {
        case Direction::NORTH: return position.y == 0;
        case Direction::EAST: return position.x == 9;
        case Direction::SOUTH: return position.y == 9;
        case Direction::WEST: return position.x == 0;
        default: return false;
    }
}
