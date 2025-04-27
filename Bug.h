// https://www.youtube.com/watch?v=oIV2KchSyGQ
// https://www.youtube.com/watch?v=JU8DbwBvOWE

#ifndef BUG_H
#define BUG_H

#include <vector>
#include <string>
#include "Position.h"
#include "Direction.h"

class Bug {
protected:
    int id;                     // Identification number for a bug
    Position position;          // Position on the board
    Direction direction;        // Direction the bug is facing
    int size;                   // Size of the bug (initially 1-20)
    bool alive;                 // Life status of the bug
    std::vector<Position> path; // Path taken by the bug
    std::string deathReason;    // Reason for death if bug is dead

public:
    // Constructor
    Bug(int id, const Position& pos, Direction dir, int size);
    
    // Destructor
    virtual ~Bug() = default;
    
    // Pure virtual function that must be implemented by derived classes
    virtual void move() = 0;
    
    // Common functionality for all bugs
    bool isWayBlocked() const;
    
    // Clone function for polymorphic copying
    virtual Bug* clone() const = 0;
    
    // Getters
    int getId() const { return id; }
    const Position& getPosition() const { return position; }
    Direction getDirection() const { return direction; }
    int getSize() const { return size; }
    bool isAlive() const { return alive; }
    const std::vector<Position>& getPath() const { return path; }
    virtual std::string getType() const = 0;
    const std::string& getDeathReason() const { return deathReason; }
    
    // Setters
    void setSize(int newSize) { size = newSize; }
    void setAlive(bool status) { alive = status; }
    void setDeathReason(const std::string& reason) { deathReason = reason; }
};

#endif // BUG_H
