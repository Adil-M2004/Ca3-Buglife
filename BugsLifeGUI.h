#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"

class BugsLifeGUI {
private:
    sf::RenderWindow window;
    Board& board;
    sf::Font font;
    
    // Grid properties
    const int cellSize = 50;
    const int gridSize = 10;
    const int windowWidth = gridSize * cellSize;
    const int windowHeight = gridSize * cellSize;
    
    // Colors
    sf::Color backgroundColor = sf::Color(240, 240, 240);
    sf::Color gridColor = sf::Color(200, 200, 200);
    sf::Color crawlerColor = sf::Color::Red;
    sf::Color hopperColor = sf::Color::Blue;
    
    // Shapes for bugs
    sf::CircleShape crawlerShape;
    sf::CircleShape hopperShape;
    
    // Text for displaying bug info
    sf::Text bugInfoText;
    
    // Helper methods
    void drawGrid();
    void drawBugs();
    void drawBugInfo(const Bug* bug, float x, float y);
    
public:
    BugsLifeGUI(Board& board);
    ~BugsLifeGUI();
    
    void run();
    void update();
    void render();
    
    // Event handling
    void handleEvents();
    void handleKeyPress(sf::Keyboard::Key key);
    void handleMouseClick(int x, int y);
};
