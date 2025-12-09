#ifndef FOOD_H
#define FOOD_H

#include "Utilities.h"
#include "Snake.h"

class Food {
private:
    Point position;
    int gridSize;
    
public:
    Food(int gridSize);
    
    void generateNewPosition(Snake& snake);
    Point getPosition() const;
    bool isEaten(Point snakeHead) const;
};

#endif