#ifndef STAGE_H
#define STAGE_H

#include "Utilities.h"
#include "Snake.h"
#include "Food.h"

class Stage {
private:
    char** grid;
    int size;
    
public:
    Stage(int gridSize);
    ~Stage();
    
    void clear();
    void placeSnake(Snake& snake);
    void placeFood(Food& food);
    void display() const;
    
    bool checkWallCollision(Point head) const;
    int getSize() const;
};

#endif