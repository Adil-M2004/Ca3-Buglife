#include "Board.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

Board::Board() {
    // Constructor implementation
}

Board::~Board() {
    // Clean up dynamically allocated bugs
    for (Crawler* bug : crawlers) {
        delete bug;
    }
    crawlers.clear();
}

void Board::initializeBoard() {
    loadBugsFromFile("crawler-bugs.txt");
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
        int id, x, y, size, direction;

        iss >> type >> id >> x >> y >> size >> direction;

        if (type == 'C') { // Assuming 'C' for Crawler
            Position pos(x, y);
            Direction dir = static_cast<Direction>(direction);
            crawlers.push_back(new Crawler(id, pos, dir, size));
        }
        // Add other bug types if needed
    }
    file.close();
}

void Board::displayBugs() const {
    std::cout << "All Bugs:\n";
    std::cout << std::left << std::setw(5) << "ID" << std::setw(10) << "Type"
              << std::setw(10) << "Position" << std::setw(8) << "Size"
              << std::setw(10) << "Direction" << std::setw(8) << "Status\n";

    for (const Crawler* bug : crawlers) {
        std::cout << std::left << std::setw(5) << bug->getId()
                  << std::setw(10) << bug->getType()
                  << std::setw(10) << bug->getPosition().toString()
                  << std::setw(8) << bug->getSize()
                  << std::setw(10) << directionToString(bug->getDirection())
                  << std::setw(8) << (bug->isAlive() ? "Alive" : "Dead") << "\n";
    }
}

void Board::findBug(int bugId) const {
    auto it = std::find_if(crawlers.begin(), crawlers.end(),
        [bugId](const Bug* bug) { return bug->getId() == bugId; });

    if (it != crawlers.end()) {
        const Bug* bug = *it;
        std::cout << "Bug found:\n";
        std::cout << "ID: " << bug->getId() << "\n";
        std::cout << "Type: " << bug->getType() << "\n";
        std::cout << "Position: " << bug->getPosition().toString() << "\n";
        std::cout << "Size: " << bug->getSize() << "\n";
        std::cout << "Direction: " << directionToString(bug->getDirection()) << "\n";
        std::cout << "Status: " << (bug->isAlive() ? "Alive" : "Dead") << "\n";
    } else {
        std::cout << "Bug " << bugId << " not found.\n";
    }
}

void Board::tapBoard() {
    for (Crawlers* bug : crawlers) {
        if (bug->isAlive()) {
            bug->move();
            // Check for collisions after each move
        }
    }
    // Additional logic for checking collisions between bugs
}

void Board::displayLifeHistory() const {
    for (const Crawlers* bug : crawlers) {
        std::cout << bug->getId() << " " << bug->getType() << " Path: ";
        const auto& path = bug->getPath();
        for (const Position& pos : path) {
            std::cout << pos.toString();
            if (&pos != &path.back()) {
                std::cout << ",";
            }
        }
        if (!bug->isAlive()) {
            std::cout << " " << bug->getDeathReason();
        }
        std::cout << "\n";
    }
}

void Board::displayAllCells() const {
    // Determine board boundaries
    int maxX = 0, maxY = 0;
    for (const Bug* bug : crawlers) {
        maxX = std::max(maxX, bug->getPosition().x);
        maxY = std::max(maxY, bug->getPosition().y);
    }

    // Display each cell
    for (int y = 0; y <= maxY; ++y) {
        for (int x = 0; x <= maxX; ++x) {
            Position current(x, y);
            std::vector<const Crawler*> bugsInCell;

            for (const Crawler* bug : crawlers) {
                if (bug->getPosition() == current) {
                    bugsInCell.push_back(bug);
                }
            }

            std::cout << "(" << x << "," << y << "): ";
            if (bugsInCell.empty()) {
                std::cout << "empty";
            } else {
                for (size_t i = 0; i < bugsInCell.size(); ++i) {
                    std::cout << bugsInCell[i]->getType() << " " << bugsInCell[i]->getId();
                    if (i < bugsInCell.size() - 1) {
                        std::cout << ", ";
                    }
                }
            }
            std::cout << "\n";
        }
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

    for (const Crawler* bug : crawlers) {
        outFile << bug->getId() << " " << bug->getType() << " Path: ";
        const auto& path = bug->getPath();
        for (const Position& pos : path) {
            outFile << pos.toString();
            if (&pos != &path.back()) {
                outFile << ",";
            }
        }
        if (!bug->isAlive()) {
            outFile << " " << bug->getDeathReason();
        }
        outFile << "\n";
    }
    outFile.close();
}

// Rule of Three implementations
Board::Board(const Board& other) {
    for (const Crawler* bug : other.crawlers) {
        crawlers.push_back(bug->clone());
    }
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        // Clear current bugs
        for (Crawler* bug : crawlers) {
            delete bug;
        }
        crawlers.clear();

        // Copy bugs from other
        for (const Crawler* bug : other.crawlers) {
            crawlers.push_back(bug->clone());
        }
    }
    return *this;
}