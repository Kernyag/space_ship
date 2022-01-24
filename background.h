#include "raylib.h"

class Background
{
public:
    Background(int winWidth, int winHeight);
    void drawBackground();
    void drawClouds();
private:
    int windowDimensions[2]{};
    Texture2D background = LoadTexture("textures/desert-backgorund.png");
    Texture2D clouds = LoadTexture("textures/clouds-transparent.png");
    float bgY{0};
    float bgScale{4};
    float clouds1YVe{120};
    float clouds2YVe{80};
    float clouds1Pos{0.f - clouds.height * bgScale * 4.f};
    float clouds2Pos{0.f - windowDimensions[1]}; 
};