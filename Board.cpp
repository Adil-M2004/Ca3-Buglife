#include "Board.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

Board::Board() {
    // Constructor implementation
}

Board::~Board() {
    // Clean up dynamically allocated bugs
    for (Bug* bug : bugs) {
        delete bug;
    }
    bugs.clear();
}

void Board::initializeBoard() {
    loadBugsFromFile("crawler-bugs");
    updateCells();
}

void Board::loadBugsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char type;
        int id, x, y, size, direction, hopLength;
        char comma; // To handle commas in the input format

        iss >> type >> comma >> id >> comma >> x >> comma >> y >> comma >> size >> comma >> direction;

        Position pos(x, y);
        Direction dir = static_cast<Direction>(direction);

        if (type == 'C') { // Crawler
            bugs.push_back(new Crawler(id, pos, dir, size));
        } else if (type == 'H') { // Hopper
            iss >> comma >> hopLength;
            bugs.push_back(new Hopper(id, pos, dir, size, hopLength));
        }
        // Add other bug types if needed
    }
    file.close();
}

void Board::displayAllBugs() const {
    std::cout << "All Bugs:\n";
    std::cout << std::left << std::setw(5) << "ID" << std::setw(10) << "Type"
              << std::setw(10) << "Position" << std::setw(8) << "Size"
              << std::setw(10) << "Direction";
    
    // Add hopLength column header for Hopper bugs if any exist
    bool hasHoppers = std::any_of(bugs.begin(), bugs.end(), 
                                 [](const Bug* bug) { return bug->getType() == "Hopper"; });
    if (hasHoppers) {
        std::cout << std::setw(10) << "HopLength";
    }
    
    std::cout << std::setw(8) << "Status\n";

    for (const Bug* bug : bugs) {
        std::cout << std::left << std::setw(5) << bug->getId()
                  << std::setw(10) << bug->getType()
                  << std::setw(10) << bug->getPosition().toString()
                  << std::setw(8) << bug->getSize()
                  << std::setw(10) << directionToString(bug->getDirection());
        
        // Display hopLength for Hopper bugs
        if (hasHoppers) {
            if (bug->getType() == "Hopper") {
                const Hopper* hopper = dynamic_cast<const Hopper*>(bug);
                std::cout << std::setw(10) << hopper->getHopLength();
            } else {
                std::cout << std::setw(10) << " ";
            }
        }
        
        std::cout << std::setw(8) << (bug->isAlive() ? "Alive" : "Dead") << "\n";
    }
}

void Board::findBug(int bugId) const {
    auto it = std::find_if(bugs.begin(), bugs.end(),
        [bugId](const Bug* bug) { return bug->getId() == bugId; });

    if (it != bugs.end()) {
        const Bug* bug = *it;
        std::cout << "Bug found:\n";
        std::cout << "ID: " << bug->getId() << "\n";
        std::cout << "Type: " << bug->getType() << "\n";
        std::cout << "Position: " << bug->getPosition().toString() << "\n";
        std::cout << "Size: " << bug->getSize() << "\n";
        std::cout << "Direction: " << directionToString(bug->getDirection()) << "\n";
        
        // Display hopLength for Hopper bugs
        if (bug->getType() == "Hopper") {
            const Hopper* hopper = dynamic_cast<const Hopper*>(bug);
            std::cout << "Hop Length: " << hopper->getHopLength() << "\n";
        }
        
        std::cout << "Status: " << (bug->isAlive() ? "Alive" : "Dead") << "\n";
        
        if (!bug->isAlive()) {
            std::cout << "Death Reason: " << bug->getDeathReason() << "\n";
        }
    } else {
        std::cout << "Bug " << bugId << " not found.\n";
    }
}

void Board::updateCells() {
    // Clear the current cell mapping
    cells.clear();
    
    // Populate cells with alive bugs
    for (Bug* bug : bugs) {
        if (bug->isAlive()) {
            Position pos = bug->getPosition();
            std::pair<int, int> cell = {pos.x, pos.y};
            cells[cell].push_back(bug);
        }
    }
}

void Board::processFights() {
    // Process fights in each cell
    for (auto& cell : cells) {
        std::vector<Bug*>& bugsInCell = cell.second;
        
        // Skip cells with 0 or 1 bug
        if (bugsInCell.size() <= 1) continue;
        
        // Find the biggest bug in the cell
        Bug* winner = nullptr;
        int maxSize = 0;
        
        std::vector<Bug*> equalSizeBugs;
        
        for (Bug* bug : bugsInCell) {
            if (bug->getSize() > maxSize) {
                maxSize = bug->getSize();
                winner = bug;
                equalSizeBugs.clear();
                equalSizeBugs.push_back(bug);
            } else if (bug->getSize() == maxSize) {
                equalSizeBugs.push_back(bug);
            }
        }
        
        // If there are multiple bugs with the same size, pick one at random
        if (equalSizeBugs.size() > 1) {
            int randomIndex = rand() % equalSizeBugs.size();
            winner = equalSizeBugs[randomIndex];
        }
        
        // Winner eats all other bugs in the cell
        int sizeGain = 0;
        for (Bug* bug : bugsInCell) {
            if (bug != winner && bug->isAlive()) {
                bug->setAlive(false);
                bug->setDeathReason("Eaten by Bug " + std::to_string(winner->getId()));
                sizeGain += bug->getSize();
            }
        }
        
        // Winner grows by the sum of the sizes of the bugs it eats
        if (sizeGain > 0) {
            winner->setSize(winner->getSize() + sizeGain);
        }
    }
}

void Board::tapBoard() {
    // Move all alive bugs
    for (Bug* bug : bugs) {
        if (bug->isAlive()) {
            bug->move();
        }
    }
    
    // Update cell mapping
    updateCells();
    
    // Process fights
    processFights();
}

void Board::displayLifeHistory() const {
    for (const Bug* bug : bugs) {
        std::cout << bug->getId() << " " << bug->getType() << " Path: ";
        const auto& path = bug->getPath();
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i].toString();
            if (i < path.size() - 1) {
                std::cout << ",";
            }
        }
        
        if (bug->isAlive()) {
            std::cout << " Alive!";
        } else {
            std::cout << " " << bug->getDeathReason();
        }
        std::cout << "\n";
    }
}

void Board::displayAllCells() const {
    // Determine board boundaries
    int maxX = 0, maxY = 0;
    for (const Bug* bug : bugs) {
        if (bug->isAlive()) {
            maxX = std::max(maxX, bug->getPosition().x);
            maxY = std::max(maxY, bug->getPosition().y);
        }
    }
    
    // Ensure minimum 10x10 board
    maxX = std::max(maxX, 9);
    maxY = std::max(maxY, 9);

    // Display each cell
    for (int y = 0; y <= maxY; ++y) {
        for (int x = 0; x <= maxX; ++x) {
            std::pair<int, int> cell = {x, y};
            std::cout << "(" << x << "," << y << "): ";
            
            auto it = cells.find(cell);
            if (it == cells.end() || it->second.empty()) {
                std::cout << "empty";
            } else {
                const std::vector<Bug*>& bugsInCell = it->second;
                for (size_t i = 0; i < bugsInCell.size(); ++i) {
                    if (bugsInCell[i]->isAlive()) {
                        std::cout << bugsInCell[i]->getType() << " " << bugsInCell[i]->getId();
                        if (i < bugsInCell.size() - 1) {
                            std::cout << ", ";
                        }
                    }
                }
            }
            std::cout << "\n";
        }
    }
}

void Board::runSimulation(int seconds) {
    int interval = 1; // seconds between taps
    int remainingBugs = 0;
    
    do {
        tapBoard();
        displayAllBugs();
        std::cout << "\n";
        
        // Count remaining alive bugs
        remainingBugs = 0;
        for (const Bug* bug : bugs) {
            if (bug->isAlive()) {
                remainingBugs++;
            }
        }
        
        std::cout << "Remaining bugs: " << remainingBugs << "\n\n";
        
        // Sleep for the specified interval
        std::this_thread::sleep_for(std::chrono::seconds(interval));
        
        seconds -= interval;
    } while (seconds > 0 && remainingBugs > 1);
    
    if (remainingBugs <= 1) {
        std::cout << "Simulation ended - Last Bug Standing!\n";
        for (const Bug* bug : bugs) {
            if (bug->isAlive()) {
                std::cout << "Winner: " << bug->getType() << " " << bug->getId() 
                          << " with size " << bug->getSize() << "\n";
                break;
            }
        }
    } else {
        std::cout << "Simulation time limit reached.\n";
    }
}

void Board::writeLifeHistoryToFile() const {
    // Get current date and time for filename
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::ostringstream filename;
    filename << "bugs_life_history_"
             << 1900 + ltm->tm_year << "_"
             << 1 + ltm->tm_mon << "_"
             << ltm->tm_mday << "_"
             << ltm->tm_hour << "_"
             << ltm->tm_min << "_out.txt";

    std::ofstream outFile(filename.str());
    if (!outFile.is_open()) {
        throw std::runtime_error("Could not create output file");
    }

    for (const Bug* bug : bugs) {
        outFile << bug->getId() << " " << bug->getType() << " Path: ";
        const auto& path = bug->getPath();
        for (size_t i = 0; i < path.size(); ++i) {
            outFile << path[i].toString();
            if (i < path.size() - 1) {
                outFile << ",";
            }
        }
        
        if (bug->isAlive()) {
            outFile << " Alive!";
        } else {
            outFile << " " << bug->getDeathReason();
        }
        outFile << "\n";
    }
    
    outFile.close();
    std::cout << "Life history written to " << filename.str() << "\n";
}

// Rule of Three implementations
Board::Board(const Board& other) {
    for (const Bug* bug : other.bugs) {
        bugs.push_back(bug->clone());
    }
    updateCells();
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        // Clear current bugs
        for (Bug* bug : bugs) {
            delete bug;
        }
        bugs.clear();

        // Copy bugs from other
        for (const Bug* bug : other.bugs) {
            bugs.push_back(bug->clone());
        }
        
        updateCells();
    }
    return *this;
}
