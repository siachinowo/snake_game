#ifndef UTILITIES_H
#define UTILITIES_H

struct Point {
    int x;
    int y;
    
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

#endif