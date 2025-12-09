#include "../include/Food.h"
#include "../include/Snake.h"
#include <cstdlib>
#include <ctime>

Food::Food(int size) {
    gridSize = size;
    srand(time(NULL));
    position.x = rand() % gridSize;
    position.y = rand() % gridSize;
}

void Food::generateNewPosition(Snake& snake) {
    int valid;
    do {
        valid = 1;
        position.x = rand() % gridSize;
        position.y = rand() % gridSize;
        
        for (int i = 0; i < snake.getLength(); i++) {
            Point bodyPart = snake.getBodyPart(i);
            if (position.x == bodyPart.x && position.y == bodyPart.y) {
                valid = 0;
                break;
            }
        }
    } while (!valid);
}

Point Food::getPosition() const {
    return position;
}

bool Food::isEaten(Point snakeHead) const {
    return (snakeHead.x == position.x && snakeHead.y == position.y);
}