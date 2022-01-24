#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"

class Character
{
public:
    // constructor
    Character(int winWidth, int winHeight);
    // getters
    Vector2 getPos() { return charPos; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    Rectangle getRecDest();
    bool getAilve() { return alive; }
    int getHealth() { return health; }
    int getAmmo() { return bullets; }
    // setters
    void setAmmo() { bullets += 10;}
    void setHealth() { health += 1; }
    // functions
    void Tick(float deltaTime);
    void undoMovementX();
    void undoMovementY();
    void loseHealth(int damage);
    void ammoFired();

private:
    Texture2D texture = LoadTexture("character/ship.png");
    Vector2 charPos{};
    Vector2 charPosLastFrame{};
    bool isTurning{};
    int rightLeft{0};
    int frame[2]{2, 0};
    int maxFrame[2]{5, 2};
    float width{};
    float height{};
    float updateTime{1.f / 12.f};
    float runningTime{};
    int speed{6};
    float scale{4.f};
    bool alive{true};
    int health{3};
    int bullets{10};
};

#endif
