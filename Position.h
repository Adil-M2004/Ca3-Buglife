#ifndef POSITION_H
#define POSITION_H

#include <string>

struct Position {
    int x;  // x coordinate
    int y;  // y coordinate

    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    std::string toString() const {
        return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
    }
};

#endif // POSITION_H
