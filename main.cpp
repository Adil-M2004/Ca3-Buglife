#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.h"
#include "BugsLifeGUI.h"

using namespace std;

void runConsoleMode(Board& board);
void runGUIMode(Board& board);

int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Create board
    Board board;
    
    // Ask user which mode to run
    char mode;
    cout << "Choose mode: (C)onsole or (G)UI? ";
    cin >> mode;
    
    if (toupper(mode) == 'G') {
        // Initialize board before starting GUI
        board.initializeBoard();
        cout << "Starting GUI mode. Controls:\n";
        cout << "- Space: Tap the board (move bugs once)\n";
        cout << "- R: Run simulation for 5 steps\n";
        cout << "- Click on a cell to see bug details in console\n";
        cout << "- ESC: Exit\n";
        runGUIMode(board);
    } else {
        runConsoleMode(board);
    }
    
    return 0;
}

void runGUIMode(Board& board) {
    BugsLifeGUI gui(board);
    gui.run();
}

void runConsoleMode(Board& board) {
    int choice;
    
    do {
        cout << "\nBug's Life Menu:\n";
        cout << "1. Initialize Bug Board (load data from file)\n";
        cout << "2. Display all Bugs\n";
        cout << "3. Find a Bug (given an id)\n";
        cout << "4. Tap the Bug Board (cause all to move, then fight/eat)\n";
        cout << "5. Display Life History of all Bugs (path taken)\n";
        cout << "6. Display all Cells listing their Bugs\n";
        cout << "7. Run simulation (generates a Tap every second)\n";
        cout << "8. Exit (write Life History of all Bugs to file)\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        try {
            switch (choice) {
                case 1:
                    board.initializeBoard();
                    cout << "Bug Board initialized.\n";
                    break;
                    
                case 2:
                    board.displayAllBugs();
                    break;
                    
                case 3: {
                    int id;
                    cout << "Enter bug ID: ";
                    cin >> id;
                    board.findBug(id);
                    break;
                }
                
                case 4:
                    board.tapBoard();
                    cout << "Board tapped. All bugs have moved and fights resolved.\n";
                    break;
                    
                case 5:
                    board.displayLifeHistory();
                    break;
                    
                case 6:
                    board.displayAllCells();
                    break;
                    
                case 7: {
                    int seconds;
                    cout << "Enter simulation duration in seconds: ";
                    cin >> seconds;
                    board.runSimulation(seconds);
                    break;
                }
                
                case 8:
                    board.writeLifeHistoryToFile();
                    cout << "Goodbye!\n";
                    break;
                    
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
        
    } while (choice != 8);
}
