#include "raylib.h"
#include "character.h"

class Assets
{
public:
    Assets(Texture2D tex, int winWidth, int winHeight);
    Rectangle getRecDest();
    void tick(float deltaTime);
    void setPos(Vector2 newPos);
    void pickUpAmmo();
    void pickUpHealth();
    void setPlayer(Character* target) { player = target; }
    void setColor(Color enemyColor) { color = enemyColor; }

private:
    Character* player;
    Texture texture{};
    Vector2 Pos{};
    Vector2 speed{5, 5};
    bool active{true};
    float frame{};
    int maxFrame{2};
    float updateTime{1.f / 12.f};
    float runningTime{};
    int winDimension[2]{};
    int width{};
    int height{};
    float scale{2.f};
    Color color{};
};