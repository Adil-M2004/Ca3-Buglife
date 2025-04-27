#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"

class Hopper : public Bug {
private:
    int hopLength; // The distance that a hopper bug can hop (2-4 squares)

public:
    // Constructor
    Hopper(int id, const Position& pos, Direction dir, int size, int hopLength);
    
    // Override pure virtual functions from Bug base class
    void move() override;
    std::string getType() const override { return "Hopper"; }
    Bug* clone() const override;
    
    // Getter for hopLength
    int getHopLength() const { return hopLength; }
};

#endif // HOPPER_H
