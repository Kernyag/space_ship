#include "assets.h"
#include "raymath.h"

Assets::Assets(Texture2D tex, int winWidth, int winHeight) : texture(tex)
{
    winDimension[0] = winWidth;
    winDimension[1] = winHeight;
    width = texture.width / 2.f;
    height = texture.height / 2.f;
    Pos.x = GetRandomValue(0, winDimension[0] - 50);
    Pos.y = GetRandomValue(-winDimension[1], -20);
}

void Assets::tick(float deltaTime)
{
    // enemy movement
    if (active)
    {
        Pos.y += speed.y;

        // reset the asset on crosing the boundary
        if (Pos.y > winDimension[1])
        {
            Pos.x = GetRandomValue(0, winDimension[0] - 50);
            Pos.y = GetRandomValue(-winDimension[1], -winDimension[1] - 500);
        }
    }

    // enemy animation
    runningTime += deltaTime;

    if (runningTime >= updateTime)
    {
        runningTime = 0.0;
        frame++;
        if (frame > maxFrame)
        {
            frame = 0;
        }
    }
    // draw enemy
    Rectangle rectSrc{
        frame * width,
        0.0,
        static_cast<float>(width),
        static_cast<float>(height)};
    Rectangle rectDest{
        Pos.x,
        Pos.y,
        scale * static_cast<float>(width),
        scale * static_cast<float>(height)};

    DrawTexturePro(texture, rectSrc, rectDest, Vector2{}, 0.f, color);
}

Rectangle Assets::getRecDest()
{
    return Rectangle{
        Pos.x,
        Pos.y,
        scale * static_cast<float>(width),
        scale * static_cast<float>(height)};
}

void Assets::setPos(Vector2 newPos)
{
    Pos = newPos;
}

void Assets::pickUpAmmo()
{
    if (CheckCollisionRecs(getRecDest(), player->getRecDest()))
    {
        player->setAmmo();
        // reset asset position
        Vector2 newAssetPos{
            static_cast<float>(GetRandomValue(0, winDimension[0])),
            static_cast<float>(GetRandomValue(0, -winDimension[1] - 500))};
        setPos(newAssetPos);
    }
}

void Assets::pickUpHealth()
{
    // pick up health
    if (CheckCollisionRecs(getRecDest(), player->getRecDest()))
    {
        if (player->getHealth() < 3)
        {
            player->setHealth();
            // reset asset position
            Vector2 newAssetPos{
                static_cast<float>(GetRandomValue(0, winDimension[0])),
                static_cast<float>(GetRandomValue(0, -winDimension[1] - 500))};
            setPos(newAssetPos);
        }
    }
}
