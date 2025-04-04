//
// Created by sahil on 03/04/2025.
//

#include "Crawler.h"

using namespace std;

Crawler::Crawler(int id, int x, int y, int dir, int size)
    : id(id), direction(dir), size(size), alive(true) {
    position.x = x;
    position.y = y;
    path.push_back(position);
}