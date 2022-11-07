#include "Tema1/lab3/lab3.h"

#include <vector>
#include <iostream>


#include "Tema1/lab3/fereastra-poarta.h"
#include "Tema1/lab3/transform2D.h"
#include "Tema1/lab3/object2D.h"

using namespace std;
using namespace Tema1;

int directie = 1, dir_tx = 1;
int tx = 150, ty = 250;
float sx = 2, sy = 2;
float rad = 50;
float rad1, rad2;
int tx1 = 150;
int dir1 = -1;

float bodyX = 200, bodyY = 400;
float wingX = 80, wingY = 125;
float rataX = 100, rataY = 300;
float update_headX, update_headY;
float angleDuck;
float headRadius = 50;
int dir_movement_X = -1, dir_movement_Y = 1, prev_dir_X = -1, prev_dir_Y = -1;
float beakX, beakY;
float wing1X, wing1Y, wing2X, wing2Y;


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

    Mesh* wing1 = object2D::CreateTriangle("wing1", corner, glm::vec3(wingX*35/100.0f, wingY, 0), glm::vec3(wingX, 0, 0), glm::vec3(88/255.0f, 58/255.0f, 39/255.0f));
    AddMeshToList(wing1);

    Mesh* wing2 = object2D::CreateTriangle("wing2", corner, glm::vec3(wingX*35/100.0f, wingY, 0), glm::vec3(wingX, 0, 0), glm::vec3(88/255.0f, 58/255.0f, 39/255.0f));
    AddMeshToList(wing2);

    Mesh* body = object2D::CreateTriangle("body", corner, glm::vec3(bodyX/2.0f, bodyY, 0), glm::vec3(bodyX, 0, 0), glm::vec3(88/255.0f, 58/255.0f, 39/255.0f));
    AddMeshToList(body);

    Mesh* beak = object2D::CreateTriangle("beak", corner, glm::vec3(25, 100, 0), glm::vec3(50, 0, 0), glm::vec3(231/255.0f, 204/255.0f, 57/255.0f));
    AddMeshToList(beak);

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



    rad1 += 2*deltaTimeSeconds * dir1;

    rad2 += 2*deltaTimeSeconds * -dir1;
    rataX += 100*deltaTimeSeconds * dir_movement_X;
    rataY += 100*deltaTimeSeconds * dir_movement_Y;

    float cosA = cos(angleDuck), sinA = sin(angleDuck);
    sx = 0.25f;
    // update_headX = rataX + (bodyX/2.0f * cosA - bodyY*sinA) * sx/1.25f;
    // update_headY = rataY + (bodyY*cosA + bodyX/2.0f*sinA) * sx;
    if(update_headX > resolution.x) {
        // margine dreapta
        rataX = update_headX;
        rataY = update_headY;
        // prev_dir_X = dir_movement_X;
        // prev_dir_Y = dir_movement_Y;
        dir_movement_X = -1;
        // dir_movement_Y = -1;
    }
    else if(update_headX < 0) {
        // margine stanga
        rataX = update_headX;
        rataY = update_headY;
        dir_movement_X = 1;
        // dir_movement_Y = 1;
    }
    else if(update_headY > resolution.y) {
        // margine sus
        rataX = update_headX;
        rataY = update_headY;
        // dir_movement_X = 1;
        dir_movement_Y = -1;
    }
    else if(update_headY < 0) {
        // margine jos
        rataX = update_headX;
        rataY = update_headY;
        // dir_movement_X = 1;
        dir_movement_Y = 1;
    }

    if(dir_movement_X == 1 && dir_movement_Y == 1) {
        //going 45 degrees clockwise
        angleDuck = M_PI * 315/180.0f; // 315 degrees
        update_headX = rataX + (bodyX/2.0f * cosA - bodyY*sinA) * sx/1.25f;
        update_headY = rataY + (bodyY*cosA + bodyX/2.0f*sinA) * sx;
        beakX = update_headX + headRadius * 1.35f;
        beakY = update_headY + headRadius * 0.3f;
        wing1X = update_headX;
        wing1Y = update_headY - headRadius * 2.0f;
        wing2X = update_headX + headRadius * 0.65f;
        wing2Y = update_headY - headRadius * 0.45f;
    }
    else if(dir_movement_X == -1 && dir_movement_Y == -1) {
        //going 135 degrees counter-clockwise
        angleDuck = M_PI * 135/180.0f;
        update_headX = rataX + (bodyX/2.0f * cosA - bodyY*sinA) * sx/1.25f;
        update_headY = rataY + (bodyY*cosA + bodyX/2.0f*sinA) * sx;
        beakX = update_headX - headRadius * 0.9f;
        beakY = update_headY - headRadius * 0.75f;
        wing1X = update_headX;
        wing1Y = update_headY + headRadius * 2.0f;
        wing2X = update_headX - headRadius * 0.65f;
        wing2Y = update_headY + headRadius * 0.65f;
    }
    else if(dir_movement_X == -1 && dir_movement_Y == 1) {
        //going 45 degrees counter-clockwise
        angleDuck = M_PI * 45/180.0f; // 315 degrees
        beakX = update_headX - headRadius;
        beakY = update_headY + headRadius * 1.0f;
        update_headX = rataX + (bodyX/2.0f * cosA - bodyY*sinA) * sx*1.0f;
        update_headY = rataY + (bodyY*cosA + bodyX/2.0f*sinA) * sx * 0.75f;
        wing1X = update_headX + headRadius * 2.15f;
        wing1Y = update_headY;


        wing2X = update_headX + headRadius * 0.7f;
        wing2Y = update_headY + headRadius * 0.6f;
    }
    else if(dir_movement_X == 1 && dir_movement_Y == -1) {
        //going 135 degrees clockwise
        angleDuck = M_PI * 225/180.0f;


        update_headX = rataX + (bodyX/2.0f * cosA - bodyY*sinA) * sx*1.0f;
        update_headY = rataY + (bodyY*cosA + bodyX/2.0f*sinA) * sx*0.75f;
        beakX = update_headX + headRadius * 0.6f;
        beakY = update_headY - headRadius * 1.2f;
        wing1X = update_headX - headRadius * 2.0f;
        wing1Y = update_headY;
        wing2X = update_headX - headRadius * 0.7f;
        wing2Y = update_headY - headRadius * 0.8f;
    }
    
    

    if(rad1 > M_PI*0.75f)
        dir1 = -1;
    if(rad1 < M_PI/2.0) {
        dir1 = 1;
    }
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Rotate(angleDuck);
    modelMatrix *= transform2D::Translate(-headRadius, -headRadius);
    // modelMatrix *= transform2D::Translate(385, 470) * transform2D::Rotate(M_PI * 3/2.0f) * transform2D::Scale(sx, sx) * transform2D::Translate(-50, -50);
    
    RenderMesh2D(meshes["head"], shaders["VertexColor"], transform2D::Translate(update_headX, update_headY) * modelMatrix);
    RenderMesh2D(meshes["body"], shaders["VertexColor"], transform2D::Translate(rataX, rataY) * transform2D::Scale(sx, sx) * modelMatrix);

    // modelMatrix *= transform2D::Translate(500, 300);
    // modelMatrix *=  transform2D::Translate(-headRadius, -headRadius);
    
    // x' = x * cos(C) - y * sin(C)

    // y' = y * cos(C) + x * sin(C)

    RenderMesh2D(meshes["beak"], shaders["VertexColor"], transform2D::Translate(beakX, beakY) * transform2D::Scale(sx, sx) * modelMatrix);

    // modelMatrix *= transform2D::Translate(475, 400) * transform2D::Scale(sx, sx) * transform2D::Rotate(rad1) * transform2D::Translate(-bodyY/2, -bodyY/2);
    RenderMesh2D(meshes["wing1"], shaders["VertexColor"], transform2D::Translate(wing1X, wing1Y) * transform2D::Rotate(rad1) * transform2D::Scale(sx, sx) * modelMatrix);    

    RenderMesh2D(meshes["wing2"], shaders["VertexColor"], transform2D::Translate(wing2X, wing2Y) * transform2D::Rotate(rad2) * transform2D::Scale(sx, sx) * modelMatrix);

    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(500, 500);


    // sx += deltaTimeSeconds *1 * directie;
    // // cout << sx << " ";
    // // cout << deltaTimeSeconds << endl;
    // if( sx >= 4) {
    //     directie = -1;
    //     sx = 4;
    // }
    // if (sx <= 1){
    //     directie = 1;
    //     sx = 1;
    // }
    
    // // TODO(student): Create animations by multiplying the current
    // // transform matrix with the matrices you just implemented
    // // Remember, the last matrix in the chain will take effect first!

    // RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    // modelMatrix = glm::mat3(1);
    // rad +=  deltaTimeSeconds * 100;
    // if(rad >= 1000)
    //     rad = 50;
    // modelMatrix *= transform2D::Translate(650, 250) * transform2D::Rotate(rad) * transform2D::Translate(-50, -50);
    // // TODO(student): Create animations by multiplying the current
    // // transform matrix with the matrices you just implemented
    // // Remember, the last matrix in the chain will take effect first!

    // RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

    // modelMatrix = glm::mat3(1);
    
    // rad1 += deltaTimeSeconds *dir1;

    // if(rad1 <= -M_PI) {
    //     rad1 = -M_PI;
    //     dir1 = 1;
    // }
    // if(rad1 >= M_PI) {
    //     rad1 = M_PI;
    //     dir1 = -1;
    // }
    
    // modelMatrix *= transform2D::Translate(650, 200) * transform2D::Rotate(rad1) * transform2D::Translate(-50, -50);
    // modelMatrix *= transform2D::Rotate(rad1) * transform2D::Translate(-50, -50);

    // RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
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


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
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
