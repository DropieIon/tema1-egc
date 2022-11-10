#include "Tema1/lab3/lab3.h"

#include <vector>
#include <iostream>


#include "Tema1/lab3/fereastra-poarta.h"
#include "Tema1/lab3/transform2D.h"
#include "Tema1/lab3/object2D.h"

using namespace std;
using namespace Tema1;

Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(100, 100, 0);

    float squareSide = 100;

    isDead = hasEscaped = false;
    start = time(NULL);

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;
    rad1 = M_PI/2.0f;
    rad2 = - M_PI/2.0f;

    // Initialize angularStep
    angularStep = 0;

    // Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
    // AddMeshToList(square1);


    // Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
    // AddMeshToList(square2);

    // Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
    // AddMeshToList(square3);

    // Mesh* square4 = object2D::CreateSquare("square4", corner, squareSide, glm::vec3(1, 0, 1));
    // AddMeshToList(square4);

    
    Mesh* head = object2D::CreateCircle("head", corner, 60, headRadius, glm::vec3(48/255.0f, 87/255.0f, 55/255.0f));
    AddMeshToList(head);

    for(int i = 0; i < nr_of_lives; i++) {
        Mesh* life = object2D::CreateCircle("life" + i, corner, 60, headRadius / 5.0f, glm::vec3(1.0f, 0, 0));
        AddMeshToList(life);
    }

    for(int i = 0; i < nr_of_bullets; i++) {
        Mesh* bullet = object2D::CreateSquare("bullet" + i, corner, 30, glm::vec3(1.0f, 204/255.0f, 0), true);
        AddMeshToList(bullet);
    }

    Mesh* wireframe = object2D::CreateRectangle("wireframe", corner, 30, headRadius * 1.2f, glm::vec3(0, 0, 1.0f));
    AddMeshToList(wireframe);


    for(int i = 0; i <= nr_of_points; i += 10) {
        Mesh* score = object2D::CreateRectangle("score" + i, corner, 28, headRadius * 1.2f * i/(float)nr_of_points, glm::vec3(0, 0.5f, 1.0f), true);
        AddMeshToList(score);
    }


    Mesh* life1 = object2D::CreateCircle("head", corner, 60, headRadius, glm::vec3(48/255.0f, 87/255.0f, 55/255.0f));
    AddMeshToList(head);

    Mesh* wing1 = object2D::CreateTriangle("wing1", corner, glm::vec3(wingX*35/100.0f, wingY, 0), glm::vec3(wingX, 0, 0), glm::vec3(88/255.0f, 58/255.0f, 39/255.0f));
    AddMeshToList(wing1);

    Mesh* wing2 = object2D::CreateTriangle("wing2", corner, glm::vec3(wingX*35/100.0f, wingY, 0), glm::vec3(wingX, 0, 0), glm::vec3(88/255.0f, 58/255.0f, 39/255.0f));
    AddMeshToList(wing2);

    Mesh* body = object2D::CreateTriangle("body", corner, glm::vec3(bodyX/2.0f, bodyY, 0), glm::vec3(bodyX, 0, 0), glm::vec3(88/255.0f, 58/255.0f, 39/255.0f));
    AddMeshToList(body);

    Mesh* beak = object2D::CreateTriangle("beak", corner, glm::vec3(25, 150, 0), glm::vec3(50, 0, 0), glm::vec3(231/255.0f, 204/255.0f, 57/255.0f));
    AddMeshToList(beak);

    hitbox1 = corner, hitbox2 = corner + glm::vec3(bodyX, bodyY, 0);

}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Lab3::DrawScene(glm::mat3 visMatrix)
{
    modelMatrix = visMatrix * transform2D::Translate(0, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(3, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(1.5, 1.5);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(0, 3);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(3, 3);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
}


void Lab3::Update(float deltaTimeSeconds)
{

    glm::ivec2 resolution = window->GetResolution();

    // tx += deltaTimeSeconds *100 * dir_tx;

    // if(tx >= 400) {
    //     dir_tx = -1;
    // }
    // if(tx <= 0) {
    //     dir_tx = 1;
    // }

    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(tx, tx);
    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented.
    // Remember, the last matrix in the chain will take effect first!

    // RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);
    sx = 0.25f;
    rad1 += 2*deltaTimeSeconds * dir_wings * wing_speed;
    rad2 += 2*deltaTimeSeconds * -dir_wings * wing_speed;
    rataX += (speed + acceleration_factor * many_dead_ducks) *deltaTimeSeconds * dir_movement_X;
    rataY += (speed + acceleration_factor * many_dead_ducks) * deltaTimeSeconds * dir_movement_Y;
    time_since_alive = time(NULL) - start;


    if(time_since_alive > 10 && !isDead) {
        // 10 seconds have passed
        start = time(NULL);
        hasEscaped = true;
    }

    if(isDead)
    {
        angleDuck = M_PI;
        dir_movement_X = 0;
        dir_movement_Y = -1;
        wing_speed = 0;
        speed = 700;
        start = time(NULL);

    }

    if(hasEscaped) {
        angleDuck = 0;
        dir_movement_X = 0;
        dir_movement_Y = 1;
        wing_speed = 10;
        speed = 100;
    }


    if(isDead && head_position_Y < 0) {
        isDead = false;
        rataX = rand() % resolution.x;
        rataY = rand() % resolution.y;
        do {
            dir_movement_X = rand() % 3 - 1;
        } while(dir_movement_X == 0);
        do {
        dir_movement_Y = rand() % 3 - 1;
        } while(dir_movement_Y == 0);
        wing_speed = 1;
        speed = speed_save;
        nr_of_bullets += 1;
    }

    if(hasEscaped && head_position_Y > resolution.y) {
        hasEscaped = false;
        rataX = rand() % resolution.x;
        rataY = rand() % resolution.y;
        do {
            dir_movement_X = rand() % 3 - 1;
        } while(dir_movement_X == 0);
        do {
        dir_movement_Y = rand() % 3 - 1;
        } while(dir_movement_Y == 0);
        wing_speed = 1;
        speed = speed_save;
        nr_of_lives -= 1;
    }

  if(head_position_X > resolution.x) {
        // margine dreapta
        // rataX = update_headX;
        // rataY = update_headY;
        // prev_dir_X = dir_movement_X;
        // prev_dir_Y = dir_movement_Y;
        dir_movement_X = -1;
        // dir_movement_Y = -1;
    }
    else if(head_position_X < 0) {
        // margine stanga
        // rataX = update_headX;
        // rataY = update_headY;
        dir_movement_X = 1;
        // dir_movement_Y = 1;
    }
    else if(head_position_Y > resolution.y) {
        // margine sus
        // rataX = update_headX;
        // rataY = update_headY;
        // dir_movement_X = 1;
        dir_movement_Y = -1;
    }
    else if(head_position_Y < 0) {
        // margine jos
        // rataX = update_headX;
        // rataY = update_headY;
        // dir_movement_X = 1;
        dir_movement_Y = 1;
    }

    // dir_movement_X = -1;
    // dir_movement_Y = -1;

    if(dir_movement_X == 1 && dir_movement_Y == 1) {
        //going 45 degrees clockwise
        angleDuck = M_PI * 315/180.0f; // 315 degrees
        // update_headX = rataX + (bodyX/2.0f * cosA - bodyY*sinA) * sx/1.25f;
        // update_headY = rataY + (bodyY*cosA + bodyX/2.0f*sinA) * sx;
        // beakX = update_headX + headRadius * 1.35f;
        // beakY = update_headY + headRadius * 0.3f;
        // wing1X = update_headX;
        // wing1Y = update_headY - headRadius * 2.0f;
        // wing2X = update_headX + headRadius * 0.65f;
        // wing2Y = update_headY - headRadius * 0.45f;
    }
    else if(dir_movement_X == -1 && dir_movement_Y == -1) {
        //going 135 degrees counter-clockwise
        angleDuck = M_PI * 135/180.0f;
        // update_headX = rataX + (bodyX/2.0f * cosA - bodyY*sinA) * sx/1.25f;
        // update_headY = rataY + (bodyY*cosA + bodyX/2.0f*sinA) * sx;
        // beakX = update_headX - headRadius * 0.9f;
        // beakY = update_headY - headRadius * 0.75f;
        // wing1X = update_headX;
        // wing1Y = update_headY + headRadius * 2.0f;
        // wing2X = update_headX - headRadius * 0.65f;
        // wing2Y = update_headY + headRadius * 0.65f;
    }
    else if(dir_movement_X == -1 && dir_movement_Y == 1) {
        //going 45 degrees counter-clockwise
        angleDuck = M_PI * 45/180.0f; // 45 degrees
        // beakX = update_headX - headRadius;
        // beakY = update_headY + headRadius * 1.0f;
        // update_headX = rataX + (bodyX/2.0f * cosA - bodyY*sinA) * sx*1.0f;
        // update_headY = rataY + (bodyY*cosA + bodyX/2.0f*sinA) * sx * 0.75f;
        // wing1X = update_headX + headRadius * 2.15f;
        // wing1Y = update_headY;


        // wing2X = update_headX + headRadius * 0.7f;
        // wing2Y = update_headY + headRadius * 0.6f;
    }
    else if(dir_movement_X == 1 && dir_movement_Y == -1) {
        //going 135 degrees clockwise
        angleDuck = M_PI * 225/180.0f;


        // update_headX = rataX + (bodyX/2.0f * cosA - bodyY*sinA) * sx*1.0f;
        // update_headY = rataY + (bodyY*cosA + bodyX/2.0f*sinA) * sx*0.75f;
        // beakX = update_headX + headRadius * 0.6f;
        // beakY = update_headY - headRadius * 1.2f;
        // wing1X = update_headX - headRadius * 2.0f;
        // wing1Y = update_headY;
        // wing2X = update_headX - headRadius * 0.7f;
        // wing2Y = update_headY - headRadius * 0.8f;
    }
    // cout << dir_movement_X << " " << dir_movement_Y << endl;
    
    if(rad1 > M_PI*0.75f)
        dir_wings = -1;
    if(rad1 < M_PI/2.0) {
        dir_wings = 1;
    }
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(sx, sx);
    modelMatrix *= transform2D::Translate(-headRadius, -headRadius);
    glm::mat3 head_pos = transform2D::Translate(rataX, rataY) * transform2D::Rotate(angleDuck) * transform2D::Translate(bodyX/2.0f * sx, bodyY* sx) * modelMatrix;
    glm::mat3 body_starting_pos = transform2D::Translate(rataX, rataY) * transform2D::Rotate(angleDuck) * modelMatrix;
    head_position_X = head_pos[2][0], head_position_Y = head_pos[2][1];
    body_starting_pos_X = body_starting_pos[2][0], body_starting_pos_Y = body_starting_pos[2][1];

    for(int i = 0; i < nr_of_lives; i++) {
        RenderMesh2D(meshes["life" + i], shaders["VertexColor"], transform2D::Translate(resolution.x - headRadius * (1.5f + i * 0.5f), resolution.y - headRadius * 1.3f) * glm::mat3(1));
    }

    for(int i = 0; i < nr_of_bullets; i++) {
        RenderMesh2D(meshes["bullet" + i], shaders["VertexColor"], transform2D::Translate(resolution.x - headRadius * (1.7f + i * 0.45f), resolution.y - headRadius * 2.5f) * glm::mat3(1));
    }
    
    
    RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], transform2D::Translate(resolution.x - headRadius * 2.6f, resolution.y - headRadius * 2.0f) * glm::mat3(1));
    RenderMesh2D(meshes["score" + (score > nr_of_points ? nr_of_points : score)], shaders["VertexColor"], transform2D::Translate(resolution.x - headRadius * 2.6f, resolution.y - headRadius * 2.0f) * glm::mat3(1));
    // modelMatrix *= transform2D::Translate(385, 470) * transform2D::Rotate(M_PI * 3/2.0f) * transform2D::Scale(sx, sx) * transform2D::Translate(-50, -50);
    RenderMesh2D(meshes["head"], shaders["VertexColor"], head_pos);
    RenderMesh2D(meshes["body"], shaders["VertexColor"], body_starting_pos);

    // modelMatrix *= transform2D::Translate(500, 300);
    // modelMatrix *=  transform2D::Translate(-headRadius, -headRadius);


    // x' = x * cos(C) - y * sin(C)

    // y' = y * cos(C) + x * sin(C)

    RenderMesh2D(meshes["beak"], shaders["VertexColor"], transform2D::Translate(rataX, rataY) * transform2D::Rotate(angleDuck) *transform2D::Translate((bodyX/2.0f +  headRadius / 3.0f)* sx, (bodyY + headRadius / 3.0f) * sx) * modelMatrix);
    // modelMatrix *= transform2D::Translate(475, 400) * transform2D::Scale(sx, sx) * transform2D::Rotate(rad1) * transform2D::Translate(-bodyY/2, -bodyY/2);

    RenderMesh2D(meshes["wing1"], shaders["VertexColor"], transform2D::Translate(rataX, rataY) * transform2D::Rotate(angleDuck) * transform2D::Translate((bodyX/2.0f - headRadius / 14.0f)* sx, (bodyY - headRadius *2.5f) * sx) * transform2D::Rotate(rad1)* modelMatrix);    
    RenderMesh2D(meshes["wing2"], shaders["VertexColor"], transform2D::Translate(rataX, rataY) * transform2D::Rotate(angleDuck) * transform2D::Translate((bodyX/2.0f +  headRadius / 3.0f)* sx, (bodyY - headRadius *1.7f) * sx) * transform2D::Rotate(rad2) * modelMatrix);
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}

bool Lab3::isPtInRectangle(int point_x, int point_y, int point1_x, int point1_y, int point2_x, int point2_y) {
    // point 1 > point 2
    point1_x -= headRadius / 2.0f;
    point1_y -= headRadius / 2.0f;
    point2_x += headRadius / 2.0f;
    point2_y += headRadius / 2.0f;
    if(point_x < point2_x && point_x > point1_x && point_y < point2_y && point_y > point1_y)
        return true;
    return false;
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    glm::ivec2 resolution = window->GetResolution();
    int actual_pos_mouse_Y = resolution.y - mouseY;
    // ray-casting algorith
    if(dir_movement_X == 1 && dir_movement_Y == 1) {
        if(isPtInRectangle(mouseX, actual_pos_mouse_Y, body_starting_pos_X, body_starting_pos_Y, head_position_X, head_position_Y)) {
            isDead = true;
        }
    }
    else if(dir_movement_X == -1 && dir_movement_Y == 1) {

        if(isPtInRectangle(mouseX, actual_pos_mouse_Y, head_position_X, body_starting_pos_Y, body_starting_pos_X, head_position_Y)) {
            isDead = true;
        }
        
    }
    else if(dir_movement_X == 1 && dir_movement_Y == -1) {
        
        if(isPtInRectangle(mouseX, actual_pos_mouse_Y, body_starting_pos_X, head_position_Y, head_position_X, body_starting_pos_Y)) {
            isDead = true;
        }

    }
    else if(dir_movement_X == -1 && dir_movement_Y == -1) {
        
        if(isPtInRectangle(mouseX, actual_pos_mouse_Y, head_position_X, head_position_Y, body_starting_pos_X, body_starting_pos_Y)) {
            isDead = true;
        }
    }

    if(isDead) {
        score += 10;
        if(score / 10 % 5 == 0)
            many_dead_ducks++;
    }

    nr_of_bullets -= 1;
    
    
    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
