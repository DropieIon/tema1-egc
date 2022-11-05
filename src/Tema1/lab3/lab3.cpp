#include "Tema1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "Tema1/lab3/transform2D.h"
#include "Tema1/lab3/object2D.h"

using namespace std;

int directie = 1, dir_tx = 1;
int tx = 150, ty = 250;
float sx = 2, sy = 2;
float rad = 50;
float rad1 = 0, rad2 = M_PI;
int tx1 = 150;
int dir1 = 1;



/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


// void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
// 	int i;
// 	int triangleAmount = 20; //# of triangles used to draw circle
	
// 	//GLfloat radius = 0.8f; //radius
// 	GLfloat twicePi = 2.0f * M_PI;
	
// 	glBegin(GL_TRIANGLE_FAN);
// 		glVertex2f(x, y); // center of circle
// 		for(i = 0; i <= triangleAmount;i++) { 
// 			glVertex2f(
// 		            x + (radius * cos(i *  twicePi / triangleAmount)), 
// 			    y + (radius * sin(i * twicePi / triangleAmount))
// 			);
// 		}
// 	glEnd();
// }

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

    float bodyX = 200, bodyY = 400;
    float wingX = 80, wingY = 125;
    
    Mesh* head = object2D::CreateCircle("head", corner, 60, 50, glm::vec3(48/255.0f, 87/255.0f, 55/255.0f));
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


void Lab3::Update(float deltaTimeSeconds)
{
    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!


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


    sx = 0.65f;
    rad1 += 2*deltaTimeSeconds * dir1;
    rad2 += 2*deltaTimeSeconds * -dir1;
    if(rad1 > M_PI/10.0f) {
        dir1 = -1;
    }
    if(rad1 < -M_PI/9.0f)
        dir1 = 1;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(425, 385) * transform2D::Scale(sx, sx) * transform2D::Rotate(rad1) * transform2D::Translate(-50, -50);
    RenderMesh2D(meshes["wing1"], shaders["VertexColor"], modelMatrix);

    

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(538, 425)* transform2D::Rotate(rad2) * transform2D::Scale(sx, sx) * transform2D::Translate(-50, -50);
    RenderMesh2D(meshes["wing2"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(500, 300);
    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);



    sx = 0.45f;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(385, 470) * transform2D::Rotate(M_PI * 3/2.0f) * transform2D::Scale(sx, sx) * transform2D::Translate(-50, -50);
    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(500, 500);
    sx = 0.45f;
    modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(625 , 425) * transform2D::Rotate(M_PI * 3/2.0f) * transform2D::Scale(sx, sx) * transform2D::Translate(-50, -50);
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

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
