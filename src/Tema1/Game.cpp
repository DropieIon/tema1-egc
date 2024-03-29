#include "Tema1/Game.h"

#include <vector>
#include <iostream>

#include "Tema1/transform2D.h"
#include "Tema1/object2D.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(100, 100, 0);

    isDead = hasEscaped = gameOver = false;
    sx = 0.25f;
    bodyX = 200;
    bodyY = 400;
    wingX = 80;
    wingY = 125;
    rataX = rand() % resolution.x;
    rataY = rand() % resolution.y;
    wing_speed = 1;
    headRadius = 100;
    do
    {
        dir_movement_X = rand() % 3 - 1;
    } while (dir_movement_X == 0);
    do
    {
        dir_movement_Y = rand() % 3 - 1;
    } while (dir_movement_Y == 0);
    speed = 300;
    speed_save = speed;
    dir_wings = 1;
    nr_of_lives = 3;
    nr_of_bullets = 3;
    nr_of_points = 100;
    score = 0;
    acceleration_factor = speed / 2.0f;
    many_dead_ducks = 0;
    start = time(NULL);

    gameRefreshColor = glm::vec3(0, 0, 0);
    rad1 = M_PI / 2.0f;
    rad2 = -M_PI / 2.0f;

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

}


void Game::FrameStart()
{
    glClearColor(gameRefreshColor[0], gameRefreshColor[1], gameRefreshColor[2], 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Game::DrawDuck() {
    glm::mat3 head_pos = transform2D::Translate(rataX, rataY) * transform2D::Rotate(angleDuck) * transform2D::Translate(bodyX/2.0f * sx, bodyY* sx) * modelMatrix;
    glm::mat3 body_starting_pos = transform2D::Translate(rataX, rataY) * transform2D::Rotate(angleDuck) * modelMatrix;
    head_position_X = head_pos[2][0], head_position_Y = head_pos[2][1];
    body_starting_pos_X = body_starting_pos[2][0], body_starting_pos_Y = body_starting_pos[2][1];

    RenderMesh2D(meshes["head"], shaders["VertexColor"], head_pos);
    RenderMesh2D(meshes["body"], shaders["VertexColor"], body_starting_pos);
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], transform2D::Translate(rataX, rataY) * transform2D::Rotate(angleDuck) *transform2D::Translate((bodyX/2.0f +  headRadius / 3.0f)* sx, (bodyY + headRadius / 3.0f) * sx) * modelMatrix);

    RenderMesh2D(meshes["wing1"], shaders["VertexColor"], transform2D::Translate(rataX, rataY) * transform2D::Rotate(angleDuck) * transform2D::Translate((bodyX/2.0f - headRadius / 14.0f)* sx, (bodyY - headRadius *2.5f) * sx) * transform2D::Rotate(rad1)* modelMatrix);    
    RenderMesh2D(meshes["wing2"], shaders["VertexColor"], transform2D::Translate(rataX, rataY) * transform2D::Rotate(angleDuck) * transform2D::Translate((bodyX/2.0f +  headRadius / 3.0f)* sx, (bodyY - headRadius *1.7f) * sx) * transform2D::Rotate(rad2) * modelMatrix);
}

void Game::DrawUI(glm::ivec2 &resolution) {

    for(int i = 0; i < nr_of_lives; i++) {
        RenderMesh2D(meshes["life" + i], shaders["VertexColor"], transform2D::Translate(resolution.x - headRadius * (1.5f + i * 0.5f), resolution.y - headRadius * 1.3f) * glm::mat3(1));
    }

    for(int i = 0; i < nr_of_bullets; i++) {
        RenderMesh2D(meshes["bullet" + i], shaders["VertexColor"], transform2D::Translate(resolution.x - headRadius * (1.7f + i * 0.45f), resolution.y - headRadius * 2.5f) * glm::mat3(1));
    }
    
    
    RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], transform2D::Translate(resolution.x - headRadius * 2.6f, resolution.y - headRadius * 2.0f) * glm::mat3(1));
    RenderMesh2D(meshes["score" + (score > nr_of_points ? nr_of_points : score)], shaders["VertexColor"], transform2D::Translate(resolution.x - headRadius * 2.6f, resolution.y - headRadius * 2.0f) * glm::mat3(1));
}



void Game::ComputeConditions(glm::ivec2 &resolution) {
    if(gameOver) {
        speed = 0;
        acceleration_factor = 0;
        wing_speed = 0;
        gameRefreshColor = glm::vec3(1.0f, 0, 0);
    }
    else if(time_since_alive > 10 && !isDead) {
        // 10 seconds have passed
        start = time(NULL);
        hasEscaped = true;
    }
    else if(isDead)
    {
        // reset game
        angleDuck = M_PI;
        dir_movement_X = 0;
        dir_movement_Y = -1;
        wing_speed = 0;
        speed = 700;
        start = time(NULL);

    }
    else if(hasEscaped) {
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
        if(nr_of_lives == 0)
            gameOver = true;
        else nr_of_bullets += 1;
    }

  if(head_position_X > resolution.x) {
        // margine dreapta
        dir_movement_X = -1;
    }
    else if(head_position_X < 0) {
        // margine stanga
        dir_movement_X = 1;
    }
    else if(head_position_Y > resolution.y) {
        // margine sus
        dir_movement_Y = -1;
    }
    else if(head_position_Y < 0) {
        // margine jos
        dir_movement_Y = 1;
    }

    if(dir_movement_X == 1 && dir_movement_Y == 1) {
        //going 45 degrees clockwise
        angleDuck = M_PI * 315/180.0f; // 315 degrees
    }
    else if(dir_movement_X == -1 && dir_movement_Y == -1) {
        //going 135 degrees counter-clockwise
        angleDuck = M_PI * 135/180.0f;
    }
    else if(dir_movement_X == -1 && dir_movement_Y == 1) {
        //going 45 degrees counter-clockwise
        angleDuck = M_PI * 45/180.0f; // 45 degrees
    }
    else if(dir_movement_X == 1 && dir_movement_Y == -1) {
        //going 135 degrees clockwise
        angleDuck = M_PI * 225/180.0f;
    }
    
    if(rad1 > M_PI*0.75f)
        dir_wings = -1;
    if(rad1 < M_PI/2.0) {
        dir_wings = 1;
    }
}

void Game::FrameEnd()
{
}


void Game::OnInputUpdate(float deltaTime, int mods)
{
}


void Game::OnKeyPress(int key, int mods)
{
}


void Game::OnKeyRelease(int key, int mods)
{
}


void Game::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

// Poetry cause I'm bored
// Duty free airport is a scam
// Visit Paris next sem
// Palais Royal seems like a good idea
// Had a creek, maybe I'll visit Ikea

// Pepper is not so nice at restaurants
// Cannon as it may be, it still haunts
// Heard myth about this spice
// I didn't arrive to suffice

// Forest, bois de boulogne is
// Drama about this there is
// A concert though could be held here
// Lots of tobacco can be smoked with beer

// Naive as it may sound
// Another idea is bound
// As loud as it can be heard
// Can you throw this word?

// Prize there is not
// Unfair it is indeed
// But news of a new competition
// In a tent nearby, could be a mission

// Verb is weird to say
// Leopard is even weirder to dismay
// To improve this poetry
// I shall bargain with thee



bool Game::isPtInRectangle(int point_x, int point_y, int point1_x, int point1_y, int point2_x, int point2_y) {
    // point 1 > point 2
    point1_x -= headRadius / 2.0f;
    point1_y -= headRadius / 2.0f;
    point2_x += headRadius / 2.0f;
    point2_y += headRadius / 2.0f;
    if(point_x < point2_x && point_x > point1_x && point_y < point2_y && point_y > point1_y)
        return true;
    return false;
}


void Game::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    glm::ivec2 resolution = window->GetResolution();
    int actual_pos_mouse_Y = resolution.y - mouseY;
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

    if(isDead && !gameOver) {
        score += 10;
        if(score / 10 % 5 == 0)
            many_dead_ducks++;
    }

    if(nr_of_bullets != 0) nr_of_bullets -= 1;
    if(!isDead && nr_of_bullets == 0) {
        hasEscaped = true;
    }
}


void Game::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Game::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Game::OnWindowResize(int width, int height)
{
}
