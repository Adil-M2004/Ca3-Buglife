#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <list>
#include <string>
#include "Bug.h"

class Board {
private:
    std::vector<Bug*> crawlers; // Vector to store pointers to Bug objects (polymorphic)

    // Private helper methods
    void loadBugsFromFile(const std::string& filename);
    void writeLifeHistoryToFile() const;

public:
    // Constructor and destructor
    Board();
    ~Board();

    // Core functionality
    void initializeBoard();
    void displayAllBugs() const;
    void findBug(int bugId) const;
    void tapBoard();
    void displayLifeHistory() const;
    void displayAllCells() const;

    // Rule of Three: Copy constructor and assignment operator
    Board(const Board& other);
    Board& operator=(const Board& other);
};

#endif // BOARD_H