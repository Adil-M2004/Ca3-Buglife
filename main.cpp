//
// Created by sahil on 04/04/2025.
//
#include <iostream>

using namespace std;
// #include "board.h"

int main()
{
    srand(time(0));
    // Board board;
    int choice;

    do {
        cout << "\nBug's Life Menu:\n";
        cout << "1. Load bugs from file\n";
        cout << "2. Display all bugs\n";
        cout << "3. Find a bug\n";
        cout << "4. Tap the board\n";
        cout << "5. Show bug paths\n";
        cout << "6. Show all cells\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: board.loadBugs("crawler-bugs.txt"); break;
            case 2: board.displayBugs(); break;
            case 3:
                int id;
            cout << "Enter bug ID: ";
            cin >> id;
            board.findBug(id);
            break;
            case 4: board.tapBoard(); break;
            case 5: board.displayLifeHistory(); break;
            case 6: board.displayAllCells(); break;
            case 7: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}