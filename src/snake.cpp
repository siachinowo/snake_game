#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "../include/Snake.h"
using namespace std;


Snake::Snake(int startX, int startY, int maxLen) {
    maxLength = maxLen;
    length = 1;
    body = new Point[maxLength];
    body[0].x = startX;
    body[0].y = startY;
    currentDirection = NONE;
    lastDirection = NONE;
}

Snake::~Snake() {
    delete[] body;
}

void Snake::setDirection(Direction dir) {
    if ((dir == UP && lastDirection == DOWN) ||
        (dir == DOWN && lastDirection == UP) ||
        (dir == LEFT && lastDirection == RIGHT) ||
        (dir == RIGHT && lastDirection == LEFT)) {
        return;
    }
    currentDirection = dir;
}

void Snake::move() {
    if (currentDirection == NONE) {
        return;
    }
    
    for (int i = length - 1; i > 0; i--) {
        body[i] = body[i - 1];
    }
    
    switch (currentDirection) {
        case UP:
            body[0].x--;
            break;
        case DOWN:
            body[0].x++;
            break;
        case LEFT:
            body[0].y--;
            break;
        case RIGHT:
            body[0].y++;
            break;
        case NONE:
            break;
    }
    
    lastDirection = currentDirection;
}

void Snake::grow() {
    if (length < maxLength) {
        length++;
    }
}

Point Snake::getHead() const {
    return body[0];
}

Point Snake::getBodyPart(int index) const {
    if (index >= 0 && index < length) {
        return body[index];
    }
    return Point(-1, -1);
}

int Snake::getLength() const {
    return length;
}

Direction Snake::getCurrentDirection() const {
    return currentDirection;
}

bool Snake::checkSelfCollision() const {
    for (int i = 1; i < length; i++) {
        if (body[0].x == body[i].x && body[0].y == body[i].y) {
            return true;
        }
    }
    return false;
}