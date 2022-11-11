#pragma once

#include "components/simple_scene.h"
#include <time.h>

class Lab3 : public gfxc::SimpleScene
{
public:
   Lab3();
   ~Lab3();

   void Init() override;

private:
   void FrameStart() override;
   void Update(float deltaTimeSeconds) override;
   void FrameEnd() override;

   void OnInputUpdate(float deltaTime, int mods) override;
   void OnKeyPress(int key, int mods) override;
   void OnKeyRelease(int key, int mods) override;
   void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
   void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
   void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
   void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
   void OnWindowResize(int width, int height) override;
   void DrawScene();
   void DrawUI(glm::ivec2 &resolution);
   bool isPtInRectangle(int point_x, int point_y, int point1_x, int point1_y, int point2_x, int point2_y);
   void ComputeConditions(glm::ivec2 &resolution);

protected:
   glm::mat3 modelMatrix, visMatrix;
   float bodyX = 200, bodyY = 400;
   float wingX = 80, wingY = 125;
   float rataX = 200, rataY = 300;
   float update_headX, update_headY;
   float angleDuck;
   float wing_speed = 1;
   float headRadius = 100;
   int dir_movement_X = -1, dir_movement_Y = -1;
   float speed = 300, speed_save = speed;
   float sx, rad1, rad2, dir_wings = 1;
   int head_position_X, head_position_Y;
   int body_starting_pos_X, body_starting_pos_Y;
   bool isDead, hasEscaped, gameOver;
   time_t time_since_alive;
   time_t start;
   int nr_of_lives = 3;
   int nr_of_bullets = 3;
   int nr_of_points = 100;
   int score = 0;
   float acceleration_factor = speed / 2.0f;
   int many_dead_ducks = 0;
   glm::vec3 gameRefreshColor;
};