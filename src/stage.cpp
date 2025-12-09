#include "../include/Stage.h"
#include "../include/Snake.h"
#include "../include/Food.h"
#include <iostream>
using namespace std;

Stage::Stage(int gridSize) {
    size = gridSize;
    grid = new char*[size];
    for (int i = 0; i < size; i++) {
        grid[i] = new char[size];
    }
}

Stage::~Stage() {
    for (int i = 0; i < size; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

void Stage::clear() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = ' ';
        }
    }
}

void Stage::placeSnake(Snake& snake) {
    for (int i = 0; i < snake.getLength(); i++) {
        Point part = snake.getBodyPart(i);
        if (part.x >= 0 && part.x < size && part.y >= 0 && part.y < size) {
            grid[part.x][part.y] = (i == 0) ? 'O' : 'o';
        }
    }
}

void Stage::placeFood(Food& food) {
    Point foodPos = food.getPosition();
    if (foodPos.x >= 0 && foodPos.x < size && foodPos.y >= 0 && foodPos.y < size) {
        grid[foodPos.x][foodPos.y] = '*';
    }
}

void Stage::display() const {
    cout << "\nCONTROLS:    W     \n";
    cout << "         A   S   D \n";
    cout << "\nPress Q to quit\n\n";
    
    for (int i = 0; i < size; i++) {
        cout << "_";
    }
    cout << "\n";
    
    for (int i = 0; i < size; i++) {
        cout << "|";
        for (int j = 0; j < size; j++) {
            cout << grid[i][j];
        }
        cout << "|\n";
    }
    
    for (int i = 0; i < size; i++) {
        cout << "_";
    }
    cout << "\n";
}

bool Stage::checkWallCollision(Point head) const {
    return (head.x < 0 || head.y < 0 || head.x >= size || head.y >= size);
}

int Stage::getSize() const {
    return size;
}