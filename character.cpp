#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width / maxFrame[0];
    height = texture.height / maxFrame[1];

    charPos = {
        static_cast<float>(winWidth) / 2.f - scale * (0.5f * width),
        static_cast<float>(winHeight) - (scale * height)};
}

void Character::Tick(float deltaTime)
{
    charPosLastFrame = charPos;

    // Ship movement
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        charPos = Vector2Add(charPos, Vector2Scale(Vector2Normalize(direction), speed));
    }

    // check direction and turning
    direction.x != 0.f ? isTurning = true : isTurning = false;

    if (direction.x < 0)
        rightLeft = -1;
    else if (direction.x > 0)
        rightLeft = 1;
    else
        rightLeft = 0;

    // update ship animation
    // update running time
    runningTime += deltaTime;

    // when is turning
    if (isTurning)
    {
        if (runningTime >= updateTime)
        {
            // update X animation frame
            runningTime = 0.0;
            if (rightLeft == -1)
            {
                frame[0] = 1;
                frame[0]--;
            }
            if (rightLeft == 1)
            {
                frame[0] = 3;
                frame[0]++;
            }
            // update Y animation frame
            frame[1]++;
            if (frame[1] > maxFrame[1])
                frame[1] = 0;
        }
    }
    // when not turning
    if (rightLeft == 0 && isTurning == false)
    {
        if (runningTime >= updateTime)
        {
            runningTime = 0.0;
            // update XY animation frame
            frame[0] = 2;
            frame[1]++;
            if (frame[1] > maxFrame[1])
                frame[1] = 0;
        }
    }

    // Draw ship
    Rectangle recSrc{frame[0] * width, frame[1] * height, width, height};
    Rectangle RecDest{charPos.x, charPos.y, scale * width, scale * height};
    DrawTexturePro(texture, recSrc, RecDest, Vector2{}, 0.f, WHITE);
    DrawRectangleLines(charPos.x, charPos.y, scale * width, scale * height, RED);
}

void Character::undoMovementX()
{
    charPos.x = charPosLastFrame.x;
}

void Character::undoMovementY()
{
    charPos.y = charPosLastFrame.y;
}

Rectangle Character::getRecDest()
{
    return Rectangle{charPos.x, charPos.y, 4.f * width, 4.f * height};
}

void Character::loseHealth(int damage)
{
    health -= damage;

    if (health == 0)
    alive = false;
}

void Character::ammoFired()
{
    bullets -=1;
}
