#include <iostream>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/string_cast.hpp>

#include <shader.hpp>
#include <shapes/square.hpp>
#include <shapes/box.hpp>

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

float mixValue = 0.2f;
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
    mixValue += 0.1f;
  if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
    mixValue -= 0.1f;
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
  window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

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

int main()
{
  GLFWwindow *window = initWindow();
  if (!window)
  {
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);

  Square *shape3D = new Box();

  glm::mat4 cubePositions[] = {
      glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, -15.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -2.2f, -2.5f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(-3.8f, -2.0f, -12.3f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(2.4f, -0.4f, -3.5f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(-1.7f, 3.0f, -7.5f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(1.3f, -2.0f, -2.5f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 2.0f, -2.5f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.2f, -1.5f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(-1.3f, 1.0f, -1.5f))
  };

  const float time = (float)glfwGetTime();
  float lastTime = time;

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

    glm::mat4 viewMatrix(1.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
    // viewMatrix = glm::rotate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
    shape3D->shaderProgram->setMat4("viewMatrix", glm::value_ptr(viewMatrix));

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    shape3D->shaderProgram->setMat4("projectionMatrix", glm::value_ptr(projectionMatrix));

    shape3D->use();

    const float time = (float)glfwGetTime();
    const float deltaTime = (time - lastTime);
    lastTime = time;

    // rotate model matrix on time
    float speed = deltaTime * 100.0f;
    cubePositions[0] = glm::rotate(cubePositions[0],  speed * glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    shape3D->modelMatrix = cubePositions[0];
    shape3D->draw();

    for(int i = 1; i < 10; i++) {
      speed = deltaTime * 25.0f;
      cubePositions[i] = glm::rotate(cubePositions[i],  speed * glm::radians(-1.0f), glm::vec3(-0.1f * i, 1.0f, 0.0f));
      shape3D->modelMatrix = cubePositions[i];
      shape3D->draw();
    }

    // Swap front and back buffers 
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }
  glfwTerminate();
}
