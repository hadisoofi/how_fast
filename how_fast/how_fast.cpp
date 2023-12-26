#include <iostream>
#include <vector>
#include <time.h>
#include "raylib.h"
using namespace std;

struct Ball {
    float x;
    float y;
    float radius;
    float speed;
    Color color;

    void draw() {
        DrawCircle(x, y, radius, color);
    }


};

Color colorArray[5] = { BLUE, GREEN, RED, PURPLE, PINK };
float radiusArray[6] = { 10, 15, 20, 25, 30, 35 };
float velocityArray[5] = { 40, 50, 60, 70, 80 };
float xPositionsArray[10] = { 90, 130, 250, 330, 400, 450, 510, 630, 670, 710 };
vector<Ball> balls;


int main()
{
    srand(time(NULL));
    char timeString[50];
    char scoreString[20];
    char finishString[100];
    bool gameOver = false;
    InitWindow(800, 600, "Overflow");
    SetTargetFPS(60);
    double startTime = GetTime();
    int score = 0;
    int scoreTextWidth = 0;
    int finishTextWidth = 0;
    double deltaTime = 1;

    while (!WindowShouldClose()) {
        deltaTime -= GetFrameTime() * 0.01;
        sprintf_s(timeString, "Time: %.1f", GetTime());
        sprintf_s(scoreString, "score: %d", score);
        scoreTextWidth = MeasureText(scoreString, 20);
        for (int i = 0; i < balls.size(); i++) {
            if (balls[i].y > GetScreenHeight() && !gameOver) {
                gameOver = true;
                sprintf_s(finishString, "Game Over. Your score is: %d hits in %.2f seconds", score, GetTime());
                finishTextWidth = MeasureText(finishString, 20);
            }
        }
        if (GetTime() - startTime > deltaTime && !gameOver) {
            startTime = GetTime();
            Ball ball = {};
            ball.x = xPositionsArray[rand() % 10];
            ball.y = -100;
            ball.speed = velocityArray[rand() % 5];
            ball.radius = radiusArray[rand() % 6];
            ball.color = colorArray[rand() % 5];
            balls.push_back(ball);
        }

        for (int i = 0; i < balls.size(); i++) {
            balls[i].y += balls[i].speed * GetFrameTime();
        }


        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !gameOver) {
            Vector2 pos = GetMousePosition();
            for (int i = 0; i < balls.size(); i++) {
                if (CheckCollisionPointCircle(pos, { balls[i].x, balls[i].y }, balls[i].radius)) {
                    balls.erase(balls.begin() + i);
                    score++;
                    break;
                }
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);
        for (int i = 0; i < balls.size(); i++) {
            balls[i].draw();
        }
        if (gameOver) {
            DrawText(finishString, GetScreenWidth() / 2 - finishTextWidth / 2, GetScreenHeight() / 2, 20, BLACK);

        }
        else {
            DrawText(timeString, 10, 10, 20, BLACK);
            DrawText(scoreString, GetScreenWidth() - scoreTextWidth - 10, 10, 20, BLACK);
        }

        EndDrawing();

    }

    CloseWindow();

}