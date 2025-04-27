#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <list>
#include <string>
#include <map>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"

class Board {
private:
    std::vector<Bug*> bugs; // Vector to store pointers to Bug objects (polymorphic)
    std::map<std::pair<int, int>, std::vector<Bug*>> cells; // Map to track bugs in each cell

    // Private helper methods
    void loadBugsFromFile(const std::string& filename);
    void updateCells();
    void processFights();
    
public:
    // Accessor for SFML GUI
    const std::map<std::pair<int, int>, std::vector<Bug*>>& getCells() const { return cells; }

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
    void runSimulation(int seconds);
    void writeLifeHistoryToFile() const;

    // Rule of Three: Copy constructor and assignment operator
    Board(const Board& other);
    Board& operator=(const Board& other);
};

#endif // BOARD_H
