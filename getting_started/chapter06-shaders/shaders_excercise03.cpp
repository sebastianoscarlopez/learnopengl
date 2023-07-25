#include <iostream>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <shader.hpp>

using namespace std;

const char *vertexPath = "./shaders/chapter06/exercise03_triangle_color_from_position.vs";
const char *fragmentPath = "./shaders/chapter06/exercise03_triangle_color_from_position.fs";

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

int main()
{
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);
  // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  float vertices_triangles[] = {
      0.5f, -0.5f, 0.0f,  // triangle bottom right
      -0.5f, -0.5f, 0.0f, // triangle bottom left
      0.0f, 0.5f, 0.0f    // triangle top
  };

  unsigned int indices_triangles[] = {
      0, 1, 2, // triangle
  };

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangles), vertices_triangles, GL_STATIC_DRAW);

  unsigned int EBO;
  glGenBuffers(1, &EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_triangles), indices_triangles, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  Shader triangleShader(vertexPath, fragmentPath);

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    // // Render here
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    triangleShader.use();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }
  glfwTerminate();
}