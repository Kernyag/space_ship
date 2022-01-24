#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "background.h"
#include "enemies.h"
#include "bullet.h"
#include <string>
#include "assets.h"
#include <sstream>

// Bullets
int NUM_SHOOTS{10};
int score{0};

int main()
{
    // window
    int windowDimensions[2]{1024, 1088};
    InitWindow(windowDimensions[0], windowDimensions[1], "Space-ship");

    // Background declaration
    Background background(windowDimensions[0], windowDimensions[1]);
    Background clouds(windowDimensions[0], windowDimensions[1]);

    // Character declaration
    Character ship(windowDimensions[0], windowDimensions[1]);

    // Enemy declaration
    Enemy smallEnemy1(LoadTexture("enemies/enemy-small.png"), windowDimensions[0], windowDimensions[1]);
    smallEnemy1.setSpeed(Vector2{3, 5});
    smallEnemy1.setHealth(1);
    Enemy smallEnemy2(LoadTexture("enemies/enemy-small.png"), windowDimensions[0], windowDimensions[1]);
    smallEnemy2.setSpeed(Vector2{3, 5});
    smallEnemy2.setHealth(1);
    Enemy smallEnemy3(LoadTexture("enemies/enemy-small.png"), windowDimensions[0], windowDimensions[1]);
    smallEnemy3.setSpeed(Vector2{3, 5});
    smallEnemy3.setHealth(1);

    Enemy bigEnemy(LoadTexture("enemies/enemy-big.png"), windowDimensions[0], windowDimensions[1]);
    bigEnemy.setSpeed(Vector2{1, 2});
    bigEnemy.setHealth(3);

    Enemy mediumEnemy1(LoadTexture("enemies/enemy-medium.png"), windowDimensions[0], windowDimensions[1]);
    mediumEnemy1.setSpeed(Vector2{2, 3});
    mediumEnemy1.setHealth(2);
    Enemy mediumEnemy2(LoadTexture("enemies/enemy-medium.png"), windowDimensions[0], windowDimensions[1]);
    mediumEnemy2.setSpeed(Vector2{2, 3});
    mediumEnemy2.setHealth(2);

    Enemy *enemies[]{
        &smallEnemy1,
        &smallEnemy2,
        &smallEnemy3,
        &bigEnemy,
        &mediumEnemy1,
        &mediumEnemy2};

    Enemy *smallEnemies[]{
        &smallEnemy1,
        &smallEnemy2,
        &smallEnemy3,
    };

    Enemy *mediumEnemies[]{
        &mediumEnemy1,
        &mediumEnemy2};

    Assets ammunition(LoadTexture("character/power-up.png"), windowDimensions[0], windowDimensions[1]);
    ammunition.setPlayer(&ship);
    ammunition.setColor(WHITE);
    Assets health(LoadTexture("character/power-up.png"), windowDimensions[0], windowDimensions[1]);
    health.setPlayer(&ship);
    health.setColor(RED);

    for (auto enemy : enemies)
    {
        enemy->setTarget(&ship);
    }

    //Bullet declaration
    Bullets bullet[NUM_SHOOTS];

    // init bullets
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        bullet[i] = Bullets{LoadTexture("character/laser-bolts.png")};
    }

    // start game loop
    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // draw background
        background.drawBackground();

        if (!ship.getAilve()) // character is dead
        {
            DrawText("Game Over!", windowDimensions[0] / 3, windowDimensions[1] / 2, 60, RED);
            std::string playerScore = "Score: ";
            playerScore.append(std::to_string(score), 0, 2);
            DrawText(playerScore.c_str(), windowDimensions[0] / 3, (windowDimensions[1] / 2) + 50, 60, YELLOW);
            EndDrawing();
            continue;
        }
        else // Character is alive
        {
            std::string shipHealth = "Health: ";
            shipHealth.append(std::to_string(ship.getHealth()), 0, 2);
            DrawText(shipHealth.c_str(), 55.f, 45.f, 40, GREEN);

            std::string shipBullets = "Bullets: ";
            shipBullets.append(std::to_string(ship.getAmmo()), 0, 2);
            DrawText(shipBullets.c_str(), 55.f, 95.f, 40, BLUE);

            std::string playerScore = "Score: ";
            playerScore.append(std::to_string(score), 0, 2);
            DrawText(playerScore.c_str(), 55.f, 145.f, 40, YELLOW);
        }

        // shoot bullets
        if (IsKeyPressed(KEY_SPACE))
        {
            if (ship.getAmmo() > 0)
            {
                ship.ammoFired();
                for (int i = 0; i < NUM_SHOOTS; i++)
                {
                    if (!bullet[i].getIsActive())
                    {
                        Vector2 projectilePos{ship.getPos().x, ship.getPos().y - ship.getHeight()};
                        bullet[i].setPos(projectilePos);
                        bullet[i].setIsActive(true);
                        break;
                    }
                }
            }
        }

        // out of ammo
        if (ship.getAmmo() == 0)
            DrawText("EMPTY", windowDimensions[0] / 2.f, windowDimensions[1] / 2.f, 40, RED);

        // update shoot movement and hide over boundary also check collision
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (bullet[i].getIsActive())
            {
                // Collision with small enemy
                for (auto enemy : smallEnemies)
                {
                    if (CheckCollisionRecs(bullet[i].getRecDest(), enemy->getRecDest()))
                    {
                        // hide the bullet
                        bullet[i].setIsActive(false);
                        // enemy damaged
                        enemy->loseHealth();
                        score += 1;
                    }
                }
                // Collision with medium enemy
                for (auto enemy : mediumEnemies)
                {
                    if (CheckCollisionRecs(bullet[i].getRecDest(), enemy->getRecDest()))
                    {
                        // hide the bullet
                        bullet[i].setIsActive(false);
                        // enemy damaged
                        enemy->loseHealth();
                        if (enemy->getAlive() == false)
                        {
                            enemy->setHealth(2);
                            enemy->setAlive(true);
                            score += 2;
                        }
                    }
                }
                // collision with big enemy
                if (CheckCollisionRecs(bullet[i].getRecDest(), bigEnemy.getRecDest()))
                {
                    // hide the bullet
                    bullet[i].setIsActive(false);
                    // enemy damaged
                    bigEnemy.loseHealth();
                    if (bigEnemy.getAlive() == false)
                    {
                        bigEnemy.setHealth(3);
                        bigEnemy.setAlive(true);
                        score += 3;
                    }
                }

                // Movement
                bullet[i].Tick(GetFrameTime());
            }
        }

        // ship movement and animation
        ship.Tick(GetFrameTime());

        // enemy movement
        for (auto enemy : enemies)
        {
            enemy->Tick(GetFrameTime());
        }

        // pick up ammunation
        ammunition.pickUpAmmo();

        // pick up health
        health.pickUpHealth();

        // ammunation movement
        ammunition.tick(GetFrameTime());
        // health movement
        health.tick(GetFrameTime());

        // check screen bounds
        if (ship.getPos().x <= 0.f ||
            ship.getPos().x + 4.f * ship.getWidth() >= windowDimensions[0])
        {
            ship.undoMovementX();
        }
        if (ship.getPos().y <= 0.f ||
            ship.getPos().y + 4.f * ship.getHeight() >= windowDimensions[1])
        {
            ship.undoMovementY();
        }

        // Draw transparent clouds
        clouds.drawClouds();

        EndDrawing();
    }
    CloseWindow();
}