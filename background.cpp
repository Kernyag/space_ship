#include "Character.h"
#include "raymath.h"
#include "background.h"

Background::Background(int winWidth, int winHeight)
{
    windowDimensions[0] = winWidth;
    windowDimensions[1] = winHeight;
}

void Background::drawBackground()
{
    // update background pos
    bgY += 60 * GetFrameTime();
    if (bgY >= background.height * bgScale)
        bgY = 0.f;

    // draw background
    Vector2 bg1Pos{0.f, bgY};
    Vector2 bg2Pos{0.f, bgY - background.height * bgScale};
    DrawTextureEx(background, bg1Pos, 0.f, bgScale, WHITE);
    DrawTextureEx(background, bg2Pos, 0.f, bgScale, WHITE);
}

void Background::drawClouds()
{
    // Draw transparent clouds
    clouds1Pos += clouds1YVe * GetFrameTime();
    clouds2Pos += clouds2YVe * GetFrameTime();
    if (clouds1Pos > windowDimensions[1])
        clouds1Pos = 0.f - clouds.height * bgScale * 4.f;
    if (clouds2Pos > windowDimensions[1])
        clouds2Pos = 0 - windowDimensions[1];

    Vector2 clouds1{0.f, clouds1Pos};
    Vector2 clouds2{0.f, clouds2Pos};
    DrawTextureEx(clouds, clouds1, 0.f, bgScale, WHITE);
    DrawTextureEx(clouds, clouds2, 0.f, bgScale, WHITE);
}