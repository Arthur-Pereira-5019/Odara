#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

extern "C"
{
#include "raylib.h"
}

using namespace std;


int expectedFPS = 60;
class Animation
{
public:
    int size;
    int frames;
    int currentFrame = 0;
    int posX;
    int posY;
    int speed; //MEASURED IN FPS
    int totalSize;
    int elapsedTime = 0;
    Texture2D atlas;
    Rectangle sheetSize;
    

    Animation(int size, int frames, int posX, int posY, int speed, string texturePath, int totalSize)
    {
        this->size = size;
        this->frames = frames;
        this->posX = posX;
        this->posY = posY;
        this->totalSize = totalSize;
        this->speed = speed;
        atlas = LoadTexture(texturePath.c_str());
        this->sheetSize = {0,0,totalSize,totalSize};

    }
    Rectangle calculateRectangle() {
        Rectangle frame = {posX+currentFrame*size,posY*size,size,size};
        return frame;
    }

    void render(int posX, int posY) {
        elapsedTime++;
        if(elapsedTime > expectedFPS/speed) {
            currentFrame++;
            elapsedTime = 0;
        }
        
        DrawTexturePro(atlas,calculateRectangle(),{posX,posY,size,size},{0,0},0,WHITE);
        if(currentFrame == frames) {
                currentFrame = 0;
        } 
    }
};

class Player
{
public:
    int speed;
    float currentSpeed;
    float movementAngle;
    int movs = 0;
    int playerX = 400;
    int playerY = 300;
    Animation *animation;
    // TODO: Create proper animator

    Player(string texturePath, int speed, int playerX, int playerY)
    {
        animation = new Animation(32, 5, 0, 1, 5, texturePath,640);
        this->speed = speed;
        this->playerX = playerX;
        this->playerY = playerY; 
    }

    void tick() {
        currentSpeed = speed;
        move();
    }

    void render() {
        animation->render(playerX,playerY);
    }

    void move() {
        if (movs > 0)
        {
            movementAngle = movementAngle / movs;
            cout << movementAngle << endl;
            playerX += currentSpeed * cos(movementAngle);
            playerY -= currentSpeed * sin(movementAngle);

            movs = 0;
        }
        movementAngle = 0;
    }
};

int main(int argc, char const *argv[])
{
    cout << "Hello, World!" << endl;
    InitWindow(800, 600, "Raylib Window");

    Texture2D atlas;
    SetTargetFPS(expectedFPS);
    
    Player *player = new Player("assets/zepelintra.png",5,400,300);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            player->movs += 1;
        }
        if (IsKeyDown(KEY_LEFT))
        {
            player->movementAngle += PI;
            player->movs += 1;

        }
        if (IsKeyDown(KEY_UP))
        {
            player->movementAngle += PI/2;
            player->movs += 1;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            player->movementAngle += 3 * PI / 2;
            player->movs += 1;
            if (IsKeyDown(KEY_RIGHT))
            {
                player->movementAngle += PI*2;
            }
        }
        player->tick();

        BeginDrawing();

        ClearBackground((Color){0, 0, 0, 255});
        player->render();

        EndDrawing();
        
    }

    CloseWindow();

    return 0;
}
