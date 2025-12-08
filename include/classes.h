#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

//===============================
// POINT STRUCTURE
//===============================
struct Point {
    int x;
    int y;
    
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};

//===============================
// DIRECTION ENUM
//===============================
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

//===============================
// SNAKE CLASS
//===============================
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

//===============================
// FOOD CLASS
//===============================
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

//===============================
// STAGE/BOARD CLASS
//===============================
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

//===============================
// COLLISION DETECTOR CLASS
//===============================
class CollisionDetector {
public:
    CollisionDetector();
    
    bool checkWallCollision(Point head, int gridSize) const;
    bool checkSelfCollision(Snake& snake) const;
    bool checkFoodCollision(Point snakeHead, Point foodPos) const;
};

//===============================
// SCORE MANAGER CLASS
//===============================
class ScoreManager {
private:
    int currentScore;
    int highScore;
    
public:
    ScoreManager();
    
    void incrementScore();
    void resetScore();
    
    int getCurrentScore() const;
    int getHighScore() const;
    
    void loadHighScore();
    void saveHighScore();
    void saveScoreHistory();
};

//===============================
// PLAYER MANAGER CLASS
//===============================
class PlayerManager {
private:
    string playerName;
    int gamesPlayed;
    int bestScore;
    
public:
    PlayerManager();
    
    void setPlayerName(string name);
    string getPlayerName() const;
    
    void incrementGamesPlayed();
    void updateBestScore(int score);
    
    int getGamesPlayed() const;
    int getBestScore() const;
    
    void displayPlayerStats() const;
};

//===============================
// GAME CLASS (Main Controller)
//===============================
class Game {
private:
    Snake* snake;
    Food* food;
    Stage* stage;
    CollisionDetector* collision;
    ScoreManager* scoreManager;
    PlayerManager* playerManager;
    
    int gridSize;
    bool gameOver;
    
public:
    Game(int size = 20);
    ~Game();
    
    void initialize();
    void run();
    void handleInput();
    void update();
    void render();
    void checkCollisions();
    void gameOverScreen();
};

#endif