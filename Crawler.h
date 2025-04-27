#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {
public:
    // Constructor
    Crawler(int id, const Position& pos, Direction dir, int size);
    
    // Override pure virtual functions from Bug base class
    void move() override;
    std::string getType() const override { return "Crawler"; }
    Bug* clone() const override;
};

#endif // CRAWLER_H
