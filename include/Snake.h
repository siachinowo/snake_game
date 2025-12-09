#ifndef SNAKE_H
#define SNAKE_H

#include "UTILITIES.H"

class Snake {
private:
    Point* body;
    int length;
    int maxLength;
    Direction currentDirection;
    Direction lastDirection;
    
public:
    Snake(int startX, int startY, int maxLen);
    ~Snake();
    
    void move();
    void setDirection(Direction dir);
    void grow();
    
    Point getHead() const;
    Point getBodyPart(int index) const;
    int getLength() const;
    Direction getCurrentDirection() const;
    
    bool checkSelfCollision() const;
};

#endif