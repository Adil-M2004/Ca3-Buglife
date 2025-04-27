#include "BugsLifeGUI.h"
#include <sstream>
#include <iostream>

BugsLifeGUI::BugsLifeGUI(Board& boardRef) : board(boardRef) {
    // Create window
    window.create(sf::VideoMode(windowWidth, windowHeight), "Bug's Life Simulation");
    window.setFramerateLimit(60);
    
    // Load font
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }


    
    // Initialize bug shapes
    crawlerShape.setRadius(cellSize / 3.0f);
    crawlerShape.setFillColor(crawlerColor);
    crawlerShape.setOrigin(cellSize / 3.0f, cellSize / 3.0f);
    
    hopperShape.setRadius(cellSize / 3.0f);
    hopperShape.setFillColor(hopperColor);
    hopperShape.setOrigin(cellSize / 3.0f, cellSize / 3.0f);
    hopperShape.setPointCount(3); // Triangle for hoppers
    
    // Initialize text
    bugInfoText.setFont(font);
    bugInfoText.setCharacterSize(10);
    bugInfoText.setFillColor(sf::Color::Black);
}

BugsLifeGUI::~BugsLifeGUI() {
    // Cleanup if needed
}

void BugsLifeGUI::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void BugsLifeGUI::update() {
    // Update game state if needed
}

void BugsLifeGUI::render() {
    window.clear(backgroundColor);
    
    drawGrid();
    drawBugs();
    
    window.display();
}

void BugsLifeGUI::drawGrid() {
    // Draw horizontal grid lines
    for (int i = 0; i <= gridSize; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, i * cellSize), gridColor),
            sf::Vertex(sf::Vector2f(windowWidth, i * cellSize), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }
    
    // Draw vertical grid lines
    for (int i = 0; i <= gridSize; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(i * cellSize, 0), gridColor),
            sf::Vertex(sf::Vector2f(i * cellSize, windowHeight), gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }
}

void BugsLifeGUI::drawBugs() {
    // Get all bugs from the board and draw them
    for (const auto& cell : board.getCells()) {
        const auto& position = cell.first;
        const auto& bugsInCell = cell.second;
        
        int x = position.first;
        int y = position.second;
        
        for (const Bug* bug : bugsInCell) {
            if (!bug->isAlive()) continue;
            
            float posX = x * cellSize + cellSize / 2.0f;
            float posY = y * cellSize + cellSize / 2.0f;
            
            if (bug->getType() == "Crawler") {
                crawlerShape.setPosition(posX, posY);
                window.draw(crawlerShape);
            } else if (bug->getType() == "Hopper") {
                hopperShape.setPosition(posX, posY);
                window.draw(hopperShape);
            }
            
            drawBugInfo(bug, posX, posY);
        }
    }
}

void BugsLifeGUI::drawBugInfo(const Bug* bug, float x, float y) {
    std::stringstream ss;
    ss << bug->getId() << " (" << bug->getSize() << ")";
    
    bugInfoText.setString(ss.str());
    bugInfoText.setPosition(x - bugInfoText.getLocalBounds().width / 2, y + cellSize / 4.0f);
    
    window.draw(bugInfoText);
}

void BugsLifeGUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            handleKeyPress(event.key.code);
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
}

void BugsLifeGUI::handleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Space:
            // Tap the board
            board.tapBoard();
            break;
        case sf::Keyboard::R:
            // Run simulation for a few steps
            for (int i = 0; i < 5; i++) {
                board.tapBoard();
            }
            break;
        case sf::Keyboard::Escape:
            window.close();
            break;
        default:
            break;
    }
}

void BugsLifeGUI::handleMouseClick(int x, int y) {
    // Convert mouse coordinates to grid coordinates
    int gridX = x / cellSize;
    int gridY = y / cellSize;
    
    // Check if coordinates are within grid bounds
    if (gridX >= 0 && gridX < gridSize && gridY >= 0 && gridY < gridSize) {
        // Find bugs at this position and display info
        std::pair<int, int> cell = {gridX, gridY};
        auto it = board.getCells().find(cell);
        
        if (it != board.getCells().end() && !it->second.empty()) {
            for (const Bug* bug : it->second) {
                std::cout << "Bug at (" << gridX << "," << gridY << "):\n";
                std::cout << "ID: " << bug->getId() << "\n";
                std::cout << "Type: " << bug->getType() << "\n";
                std::cout << "Size: " << bug->getSize() << "\n";
                std::cout << "Direction: " << directionToString(bug->getDirection()) << "\n";
                
                if (bug->getType() == "Hopper") {
                    const Hopper* hopper = dynamic_cast<const Hopper*>(bug);
                    std::cout << "Hop Length: " << hopper->getHopLength() << "\n";
                }
                
                std::cout << "Status: " << (bug->isAlive() ? "Alive" : "Dead") << "\n";
                if (!bug->isAlive()) {
                    std::cout << "Death Reason: " << bug->getDeathReason() << "\n";
                }
                std::cout << "------------------------\n";
            }
        }
    }
}
