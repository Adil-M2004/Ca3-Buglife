#ifndef DIRECTION_H
#define DIRECTION_H

enum class Direction {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
};

inline std::string directionToString(Direction dir) {
    switch (dir) {
        case Direction::NORTH: return "North";
        case Direction::EAST: return "East";
        case Direction::SOUTH: return "South";
        case Direction::WEST: return "West";
        default: return "Unknown";
    }
}

#endif // DIRECTION_H
