#include "bullet.h"
#include "raymath.h"

Bullets::Bullets(Texture2D tex) : texture(tex)
{
    width = texture.width / maxFrame;
    height = texture.height / maxFrame;
}

void Bullets::Tick(float deltaTime)
{

    // Movement
    pos.y += speed.y;

    if (getRecDest().y <= 1) // goes above the screen
    {
        active = false;
    }

    // bullet animation
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0;
        frame++;
        if (frame > maxFrame)
        {
            frame = 0;
        }
    }

    Rectangle recSrc{
        frame * width,
        static_cast<float>(height),
        static_cast<float>(width),
        static_cast<float>(height)};
    Rectangle recDest{
        pos.x,
        pos.y,
        scale * width,
        scale * height};

    //if (active)
    DrawTexturePro(texture, recSrc, recDest, Vector2{}, 0.f, WHITE);
}

Rectangle Bullets::getRecDest()
{
    return Rectangle{
        pos.x,
        pos.y,
        scale * static_cast<float>(width),
        scale * static_cast<float>(height)};
}

void Bullets::setPos(Vector2 newPos)
{
    pos = newPos;
}

void Bullets::setIsActive(bool shootActive)
{
    active = shootActive;
}
