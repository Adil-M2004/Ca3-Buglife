#ifndef CRAWLER_H
#define CRAWLER_H

#include <vector>
#include <string>

using namespace std;

struct Position
{
    int x;  // x coordinate
    int y;  // y coordinate
};

class Crawler {
public:
    int id;
    Position position;
    int direction;  // 1=N, 2=E, 3=S, 4=W
    int size;
    bool alive;
    vector<Position> path;
    
    Crawler(int id, int x, int y, int dir, int size);
    void move();
    bool isWayBlocked();
    string getDirectionName();
    string getInfo();
};

#endif //CRAWLER_H