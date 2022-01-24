#include "enemies.h"
#include "raymath.h"

Enemy::Enemy(Texture2D tex, int winWidth, int winHeight) : texture(tex)
{

    width = texture.width / 2.f;
    height = texture.height;
    winDimension[0] = winWidth;
    winDimension[1] = winHeight;
    Pos.x = GetRandomValue(0, winDimension[0] - 50);
    Pos.y = GetRandomValue(-winDimension[1], -20);
}

void Enemy::setHealth(int enemyHealth)
{
    health = enemyHealth;
}

void Enemy::Tick(float deltaTime)
{

    // enemy movement
        /*
        if (Pos.y <= 200)
        {
            Pos.y += speed.y;
        }
        else
        */
        Pos.y += speed.y;
        //Pos.y <= winDimension[1] / 2 ? Pos.y += speed.y : Pos.y += 2 * speed.y;

        if (Pos.x <= (target->getPos().x + (target->getWidth() * scale) / 2) - (width / 2) * scale)
        {
            Pos.x += speed.x;
        }

        if (Pos.x >= (target->getPos().x + (target->getWidth() * scale) / 2) - (width / 2) * scale)
        {
            Pos.x -= speed.x;
        }

        // reset the enemy on crosing the boundary
        if (Pos.y > winDimension[1])
            setPos();

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

    DrawTexturePro(texture, rectSrc, rectDest, Vector2{}, 0.f, WHITE);

    if (CheckCollisionRecs(target->getRecDest(), getRecDest()))
    {
        target->loseHealth(1);
        setPos();
    }
}

Rectangle Enemy::getRecDest()
{
    return Rectangle{
        Pos.x,
        Pos.y,
        scale * static_cast<float>(width),
        scale * static_cast<float>(height)};
}

void Enemy::setPos()
{
    Vector2 newEnemyPos{
        static_cast<float>(GetRandomValue(0, winDimension[0])),
        static_cast<float>(GetRandomValue(0, -winDimension[1] / 2.f))};
    Pos = newEnemyPos;
}

void Enemy::setSpeed(Vector2 enemySpeed)
{
    speed = enemySpeed;
}

void Enemy::loseHealth()
{
    health -= 1;
    death();
}

void Enemy::death()
{
    if (health <= 0)
    {
        setPos();
        alive = false;
    }
}