#include <iostream>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include <glm/gtx/string_cast.hpp>

#include <shader.hpp>
#include <shapes/square.hpp>
#include <shapes/box.hpp>
#include <camera_fps.hpp>

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

float speed = 0.0f;
float cameraSpeed = 0.02f;
CameraFPS camera = CameraFPS(glm::vec3(0.0f, 0.0f, 10.0f), true);

int isFirstTime = 1;
float lastX = 0.0f, lastY = 0.0f;
void mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
  if (isFirstTime)
  {
    lastX = xPos;
    lastY = yPos;
    isFirstTime = 0;
    return;
  }
  float distX = xPos - lastX;
  float distY = lastY - yPos;
  lastX = xPos;
  lastY = yPos;

  camera.rotate(distX * cameraSpeed, distY * cameraSpeed);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  switch (key)
  {
  case GLFW_KEY_ESCAPE:
    glfwSetWindowShouldClose(window, true);
    break;
  case GLFW_KEY_W:
    camera.moveForward(speed);
    break;
  case GLFW_KEY_A:
    camera.moveRight(speed);
    break;
  case GLFW_KEY_S:
    camera.moveForward(-speed);
    break;
  case GLFW_KEY_D:
    camera.moveRight(-speed);
    break;
  default:
    break;
  }
}

GLFWwindow *initWindow()
{
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return nullptr;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(800, 600, "Lighting", NULL, NULL);

  if (!window)
  {
    glfwTerminate();
    return nullptr;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return nullptr;
  }

  return window;
}

float boxVertices[] = {
    // positions          // normals
    -0.5f, -0.5f, +0.5f, +0.0f, +0.0f, +1.0f, // front bottom left
    +0.5f, -0.5f, +0.5f, +0.0f, +0.0f, +1.0f, // front bottom right
    -0.5f, +0.5f, +0.5f, +0.0f, +0.0f, +1.0f, // front top left
    +0.5f, +0.5f, +0.5f, +0.0f, +0.0f, +1.0f, // front top right

    +0.5f, -0.5f, -0.5f, +0.0f, +0.0f, -1.0f, // back bottom right
    -0.5f, -0.5f, -0.5f, +0.0f, +0.0f, -1.0f, // back bottom left
    +0.5f, +0.5f, -0.5f, +0.0f, +0.0f, -1.0f, // back top right
    -0.5f, +0.5f, -0.5f, +0.0f, +0.0f, -1.0f, // back top left

    +0.5f, -0.5f, +0.5f, +1.0f, +0.0f, +0.0f, // right front bottom
    +0.5f, -0.5f, -0.5f, +1.0f, +0.0f, +0.0f, // right back bottom
    +0.5f, +0.5f, +0.5f, +1.0f, +0.0f, +0.0f, // right front top
    +0.5f, +0.5f, -0.5f, +1.0f, +0.0f, +0.0f, // right back top

    -0.5f, -0.5f, -0.5f, -1.0f, +0.0f, +0.0f, // left back bottom
    -0.5f, -0.5f, +0.5f, -1.0f, +0.0f, +0.0f, // left front bottom
    -0.5f, +0.5f, -0.5f, -1.0f, +0.0f, +0.0f, // left back top
    -0.5f, +0.5f, +0.5f, -1.0f, +0.0f, +0.0f, // left front top

    -0.5f, +0.5f, +0.5f, +0.0f, +1.0f, +0.0f, // top left front
    +0.5f, +0.5f, +0.5f, +0.0f, +1.0f, +0.0f, // top right front
    -0.5f, +0.5f, -0.5f, +0.0f, +1.0f, +0.0f, // top left back
    +0.5f, +0.5f, -0.5f, +0.0f, +1.0f, +0.0f, // top right back

    -0.5f, -0.5f, -0.5f, +0.0f, -1.0f, +0.0f, // bottom left back
    +0.5f, -0.5f, -0.5f, +0.0f, -1.0f, +0.0f, // bottom right back
    -0.5f, -0.5f, +0.5f, +0.0f, -1.0f, +0.0f, // bottom left front
    +0.5f, -0.5f, +0.5f, +0.0f, -1.0f, +0.0f, // bottom right front
};

struct ElementIndex
{
  unsigned int triangle[3];
};

ElementIndex elementIndex[] = {
    {0, 1, 2},
    {2, 1, 3},
    {4, 5, 6},
    {6, 5, 7},
    {8, 9, 10},
    {10, 9, 11},
    {12, 13, 14},
    {14, 13, 15},
    {16, 17, 18},
    {18, 17, 19},
    {20, 21, 22},
    {22, 21, 23},
};

float colorWhite[] = {1.0f, 1.0f, 1.0f};
float colorCoral[] = {1.0f, 0.5f, 0.31f};

unsigned int boxVAO;
void setupBuffersBox()
{
  glGenVertexArrays(1, &boxVAO);
  glBindVertexArray(boxVAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);

  unsigned int EBO;
  glGenBuffers(1, &EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementIndex), elementIndex, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int main()
{
  GLFWwindow *window = initWindow();
  if (!window)
  {
    return -1;
  }
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);

  // build and compile our shader program

  Shader *boxProgram = new Shader("./shaders/chapter12/basic.vs", "./shaders/chapter12/basic.fs");
  Shader *lightProgram = new Shader("./shaders/chapter12/basic.vs", "./shaders/chapter12/light.fs");

  setupBuffersBox();
  glm::mat4 aBoxModelMatrix(1.0f);

  glm::mat4 aLightModelMatrix(1.0f);

  float lastTime = (float)glfwGetTime();
  float firstTime = (float)glfwGetTime();
  // Loop until the user closes the window

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    // // Render here
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // enable depth test
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);

    const float time = (float)glfwGetTime();
    const float deltaTime = (time - lastTime);
    const float totalTime = (time - firstTime);
    lastTime = time;
    speed = 15.0f;

    const glm::vec3 cameraPosition = glm::vec3(0.0f, -0.25f, 2.0f);
    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.01f, 10.0f);

    glBindVertexArray(boxVAO);
    lightProgram->use();

    lightProgram->setMat4("viewMatrix", glm::value_ptr(viewMatrix));
    lightProgram->setMat4("projectionMatrix", glm::value_ptr(projectionMatrix));
    lightProgram->setFloat3("cameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);

    // Light A
    const float aLightAngle = glm::radians(totalTime * speed);
    const glm::vec3 aLightPosition(glm::cos(aLightAngle), 0.5f, glm::sin(aLightAngle));
    // const glm::vec3 aLightPosition(2.0f, 0.75f, 1.0f);

    aLightModelMatrix = glm::translate(glm::mat4(1.0f), aLightPosition);
    aLightModelMatrix = glm::scale(aLightModelMatrix, 0.25f * glm::vec3(1.0f));
    lightProgram->setMat4("modelMatrix", glm::value_ptr(aLightModelMatrix));

    lightProgram->setFloat3v("lightColor", colorWhite);
    float lightStrength = 0.9f;
    lightProgram->setFloat("lightStrength", lightStrength);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Boxes
    boxProgram->use();
    boxProgram->setMat4("viewMatrix", glm::value_ptr(viewMatrix));
    boxProgram->setMat4("projectionMatrix", glm::value_ptr(projectionMatrix));
    boxProgram->setFloat3("cameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);

    float ambientColor[] = {1.0f, 1.0f, 1.0f};
    float ambientStrength = 0.1f;
    boxProgram->setFloat3v("ambientColor", ambientColor);
    boxProgram->setFloat("ambientStrength", ambientStrength);

    boxProgram->setFloat3("lightPosition", aLightPosition.x, aLightPosition.y, aLightPosition.z);
    boxProgram->setFloat3v("lightColor", colorWhite);
    boxProgram->setFloat("lightStrength", lightStrength);

    // Box A
    aBoxModelMatrix = glm::rotate(aBoxModelMatrix, glm::radians(deltaTime * speed), glm::vec3(0.0f, 1.0f, 0.0f));
    aBoxModelMatrix = glm::rotate(aBoxModelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    boxProgram->setMat4("modelMatrix", glm::value_ptr(aBoxModelMatrix));

    boxProgram->setFloat3v("color", colorCoral);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }
  glfwTerminate();
}
