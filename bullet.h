#include "raylib.h"
#include "character.h"

class Bullets
{
public:
    Bullets() { };
    Bullets(Texture2D texture);
    Rectangle getRecDest();
    bool getIsActive() { return active; }
    void setIsActive(bool shootActive);
    void setPos(Vector2 newPos);
    void Tick(float deltaTime);

private:
    Texture2D texture{};
    Vector2 speed{0, -10};
    Vector2 pos{};
    bool active{};
    float runningTime{0.f};
    float updateTime{1.f / 12.f};
    float frame{};
    int width{};
    int height{};
    float scale{4};
    float maxFrame{2};
};