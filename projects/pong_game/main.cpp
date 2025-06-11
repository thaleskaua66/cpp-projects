#include <raylib.h>
#include <iostream>
#include <string>
#include <ctime>

int player_score = 0;
int cpu_score = 0;

Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

class Ball
{
  public:
    double x, y;
    int speed_x, speed_y;
    int radius;

  void Draw(){
    DrawCircle(x, y, radius, Yellow);
  }

  void Update(){
    x += speed_x;
    y += speed_y;

    if(y + radius >= GetScreenHeight() || y - radius <= 0){
      speed_y *= -1;
    }
    if(x + radius >= GetScreenWidth()){
      cpu_score++;
      ResetBall();
    }else if(x + radius <= 0){
      player_score++;
      ResetBall();
    }
  }

  void ResetBall(){
    x = GetScreenWidth()/2;
    y = GetScreenHeight()/2;

    int speed_choices[2] = {-1, 1};
    speed_x *= speed_choices[GetRandomValue(0, 1)];
    speed_y *= speed_choices[GetRandomValue(0, 1)];
  }
};

class Paddle
{
  public:
    double x, y;
    double width, height;
    double speed;

  void Draw(){
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
  }

  void Update(){
    if(IsKeyDown(KEY_DOWN)){
      y += speed;
    }else if(IsKeyDown(KEY_UP)){
      y -= speed;
    }

    if(y <= 0){
      y = 0;
    }else if(y + height >= GetScreenHeight()){
      y = GetScreenHeight() - height;
    }
  }
};

class CpuPaddle : public Paddle
{
  public:

  void Update(int ballY){
    if(y + height/2 > ballY){
      y -=  speed;
    }else if(y + height/2 < ballY){
      y += speed;
    }
  }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main()
{
  // Window
  const int screenWidth = 640;
  const int screenHeight = 360;
  InitWindow(screenWidth, screenHeight, "Pong Game");

  // FPS
  const int FPS = 60;
  SetTargetFPS(FPS);

  // Objects

  // Ball
  ball.radius = 15;
  ball.x = screenWidth/2;
  ball.y = screenHeight/2;
  ball.speed_x = 6;
  ball.speed_y = 6;

  // Player
  player.width = 13;
  player.height = 60;
  player.x = screenWidth - player.width - 8;
  player.y = screenHeight/2 - player.height/2;
  player.speed = 6;

  // CP
  cpu.width = 13;
  cpu.height = 60;
  cpu.x = cpu.width - 8;
  cpu.y = screenHeight/2 - player.height/2;
  cpu.speed = 4.9;

  while(!WindowShouldClose())
  {
    BeginDrawing();

    // UPDATING
    ball.Update();
    player.Update();
    cpu.Update(ball.y);

    // collision
    if(CheckCollisionCircleRec(Vector2{(float)ball.x, (float)ball.y}, ball.radius, Rectangle{(float)player.x, (float)player.y, (float)player.width, (float)player.height})){
      ball.speed_x *= -1;
    }else if(CheckCollisionCircleRec(Vector2{(float)ball.x, (float)ball.y}, ball.radius, Rectangle{(float)cpu.x, (float)cpu.y, (float)cpu.width, (float)cpu.height})){
      ball.speed_x *= -1;
    }


    // DRAWING
    ClearBackground(DarkGreen);

    DrawRectangle(screenWidth/2, 0, screenWidth/2, screenHeight, Green);
    DrawCircle(screenWidth/2, screenHeight/2, 75, LightGreen);
    DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
    ball.Draw();
    cpu.Draw();
    player.Draw();

    DrawText(TextFormat("%i", cpu_score), screenWidth/4 - 20, 20, 60, WHITE);
    DrawText(TextFormat("%i", player_score), 3 * screenWidth/4 - 20, 20, 60, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}