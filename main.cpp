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

int main(int argc, char const *argv[])
{
    cout << "Hello, World!" << endl;
    InitWindow(800, 600, "Raylib Window");

    Texture2D atlas;
    SetTargetFPS(60);
    atlas = LoadTexture("assets/zepelintra.png");
    int speed = 5;
    int currentSpeed = 5;
    float movementAngle = 0;
    int movs = 0;
    int playerX = 400;
    int playerY = 300;


    while (!WindowShouldClose())
    {
        currentSpeed = speed;
        if (IsKeyDown(KEY_RIGHT)) {
            movementAngle += 0;
            movs += 1;
        }
        if (IsKeyDown(KEY_LEFT)) {
            movementAngle += PI;
            movs += 1;
        }
        if (IsKeyDown(KEY_UP)) {
            movementAngle += PI/2;
            movs += 1;
        }
        if (IsKeyDown(KEY_DOWN)) {
            movementAngle += 3*PI/2;
            movs += 1;
            if(IsKeyDown(KEY_RIGHT)) {
                  movementAngle += 2*PI;
            }
        }

        if (movs > 0)
        {
            movementAngle = movementAngle / movs;
            cout << movementAngle <<endl;
            playerX += currentSpeed * cos(movementAngle);
            playerY -= currentSpeed * sin(movementAngle);
            
            movs = 0;
        }

        BeginDrawing();

        ClearBackground((Color){0, 0, 0, 255});
        DrawText(to_string(movementAngle).c_str(),100,50,20,WHITE);
        DrawTexture(atlas, playerX, playerY, WHITE);

        EndDrawing();
        movementAngle = 0;
    }
    
    CloseWindow();

    return 0;
}
