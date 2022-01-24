#include "raylib.h"
#include "character.h"

class Enemy
{
public:
    // constructor
    Enemy() { };
    Enemy(Texture2D tex, int winWidth, int winHeight);
    // getters
    Vector2 getPos() { return Pos; }
    Rectangle getRecDest();
    int getHealth() { return health; }
    bool getAlive() { return alive; }
    // setters
    void setPos();
    void setSpeed(Vector2 speedEnemy);
    void setHealth(int enemyHealth);
    void setAlive(bool isAlive) { alive = isAlive; }
    // functions
    void Tick(float deltaTime);
    void setTarget(Character* ship) { target = ship; }
    void loseHealth();
    void death();

private:
    Character* target;
    Texture texture{};
    Vector2 Pos{};
    Vector2 speed{};
    float frame{};
    int maxFrame{2};
    float updateTime{1.f / 12.f};
    float runningTime{};
    int winDimension[2]{};
    int width{};
    int height{};
    float scale{4.f};
    int health{};
    bool alive{true};
};