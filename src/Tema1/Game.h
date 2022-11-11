#pragma once

#include "components/simple_scene.h"

class Game : public gfxc::SimpleScene
{
public:
   Game();
   ~Game();

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
   void DrawDuck();
   void DrawUI(glm::ivec2 &resolution);
   bool isPtInRectangle(int point_x, int point_y, int point1_x, int point1_y, int point2_x, int point2_y);
   void ComputeConditions(glm::ivec2 &resolution);

protected:
   glm::mat3 modelMatrix;
   float bodyX, bodyY;
   float wingX, wingY;
   float rataX, rataY;
   float update_headX, update_headY;
   float angleDuck;
   float wing_speed;
   float headRadius;
   int dir_movement_X, dir_movement_Y;
   float speed, speed_save;
   float sx, rad1, rad2, dir_wings;
   int head_position_X, head_position_Y;
   int body_starting_pos_X, body_starting_pos_Y;
   bool isDead, hasEscaped, gameOver;
   time_t time_since_alive;
   time_t start;
   int nr_of_lives;
   int nr_of_bullets;
   int nr_of_points;
   int score;
   float acceleration_factor;
   int many_dead_ducks;
   glm::vec3 gameRefreshColor;
};