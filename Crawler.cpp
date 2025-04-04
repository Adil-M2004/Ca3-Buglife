//
// Created by sahil on 03/04/2025.
//

#include "Crawler.h"

//

#include <cstdlib>
#include <ctime>

using namespace std;

Crawler::Crawler(int id, int x, int y, int dir, int size)
    : id(id), direction(dir), size(size), alive(true) {
    position.x = x;
    position.y = y;
    path.push_back(position);
}

void Crawler::move()
{
    if (!alive) return;

    while (isWayBlocked())
    {
        direction = (rand() % 4) + 1;
    }

	switch (direction)
    {
        case 1: position.y--; break; // North
        case 2: position.x++; break; // East
        case 3: position.y++; break; // South
        case 4: position.x--; break; // West
    }

    path.push_back(position);
}

bool Crawler::isWayBlocked()
{
    switch (direction)
  {
        case 1: return position.y == 0;
        case 2: return position.x == 9;
        case 3: return position.y == 9;
        case 4: return position.x == 0;
        default: return false;
    }
}

string Crawler::getDirectionName()
{
    switch (direction)
  {
        case 1: return "North";
        case 2: return "East";
        case 3: return "South";
        case 4: return "West";
        default: return "Unknown";
    }
}

string Crawler::getInfo()
{
    string status = alive ? "Alive" : "Dead";
    return to_string(id) + " at (" +
           to_string(position.x) + "," +
           to_string(position.y) + ") " +
           "Size: " + to_string(size) + " " +
           "Facing: " + getDirectionName() + " " + status;
}
