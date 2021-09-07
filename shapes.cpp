#include "raylib.h"
#include <string>
#include <cstring>

char* intToStr(int data) {
    std::string strData = std::to_string(data);

    char* temp = new char[strData.length() + 1];
    strcpy(temp, strData.c_str());

   return temp;
}

int main(void)
{
    // Initialization
    //---------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - bouncing ball");

    Vector2 ballPosition = { GetScreenWidth()/2, GetScreenHeight()/2 };
    Vector2 boxPosition = { GetScreenWidth()/2 - 20, GetScreenHeight()/2 + 75};
    //Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 10;

    //SET VARIBLES FOR SPRING
    int gravity = 10;
    int mass = 30;
    float positionY = 200;
    float positionX = 14;
    float velocityY = 0;
    float velocityX = 0;
    float timeStep = 0.28f;
    int anchorX = 209;
    int anchorY = 181;
    float k = 2;
    float damping = 5;

    bool pause = 0;
    int framesCounter = 0;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //-----------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        BeginDrawing();
        if (!pause)
        {
            ClearBackground(RAYWHITE);

            DrawText("PRESS SPACE to PAUSE SIMULATION", 10, GetScreenHeight() - 25, 20, LIGHTGRAY);
            //
            float springForceY = -k*(positionY - anchorY);
            float springForceX = -k*(positionX - anchorX);
            
            float dampingForceY = damping * velocityY;
            float dampingForceX = damping * velocityX;
            
            float forceY = springForceY + mass * gravity - dampingForceY;
            float forceX = springForceX - dampingForceX;
            
            float accelerationY = forceY/mass;
            float accelerationX = forceX/mass;
            
            velocityY = velocityY + accelerationY * timeStep;
            velocityX = velocityX + accelerationX * timeStep;
            
            
            if(IsKeyDown(KEY_D)){
                positionX = positionX + 5.0f;
            }else if(IsKeyDown(KEY_A)){
                positionX = positionX - 5.0f;
            }else if(IsKeyDown(KEY_W)){
                positionY = positionY - 5.0f;
            }else if(IsKeyDown(KEY_S)){
                positionY = positionY + 5.0f;
            }else{
                positionY = positionY + velocityY * timeStep;
                positionX = positionX + velocityX * timeStep;
            }
            // DRAW SPRING-MASS
            DrawRectangle(anchorX-5, anchorY-5, 10, 10,GRAY);
            DrawLine(positionX, positionY, anchorX, anchorY,LIGHTGRAY);
            DrawCircle(positionX, positionY, 10,RED);    
        }
        else{
            if(IsKeyDown(KEY_D)){
                positionX = positionX + 5.0f;
            }else if(IsKeyDown(KEY_A)){
                positionX = positionX - 5.0f;
            }else if(IsKeyDown(KEY_W)){
                positionY = positionY - 5.0f;
            }else if(IsKeyDown(KEY_S)){
                positionY = positionY + 5.0f;
            }
            ClearBackground(LIGHTGRAY);
            DrawRectangle(anchorX-5, anchorY-5, 10, 10,GRAY);
            DrawLine(positionX, positionY, anchorX, anchorY,GRAY);
            DrawCircle(positionX, positionY, 10,RED);
            DrawText("PRESS SPACE to PAUSE SIMULATION", 10, GetScreenHeight() - 25, 20, GRAY);
            framesCounter++;
            if ((framesCounter/30)%2) DrawText("PAUSED", 350, 200, 30, GRAY);
        } 
         EndDrawing();
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}