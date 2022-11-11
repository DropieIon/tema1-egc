#include "Tema1/Game.h"

#include <vector>
#include <iostream>

#include "Tema1/transform2D.h"
#include "Tema1/object2D.h"

using namespace std;

void Game::Update(float deltaTimeSeconds)
{

    glm::ivec2 resolution = window->GetResolution();
    rad1 += 2*deltaTimeSeconds * dir_wings * wing_speed;
    rad2 += 2*deltaTimeSeconds * -dir_wings * wing_speed;
    rataX += (speed + acceleration_factor * many_dead_ducks) *deltaTimeSeconds * dir_movement_X;
    rataY += (speed + acceleration_factor * many_dead_ducks) * deltaTimeSeconds * dir_movement_Y;
    time_since_alive = time(NULL) - start;

    ComputeConditions(resolution);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(sx, sx);
    modelMatrix *= transform2D::Translate(-headRadius, -headRadius);

    DrawUI(resolution);

    DrawDuck();
}
