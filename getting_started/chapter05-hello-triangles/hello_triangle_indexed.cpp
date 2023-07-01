#include <iostream>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

using namespace std;

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

  // float vertices[] = {
  //     -0.5f, -0.5f, 0.0f,
  //     0.5f, -0.5f, 0.0f,
  //     0.5f, 0.5f, 0.0f,
  //     -0.5f, 0.5f, 0.0f,
  //     };

  // int indices[] = {
  //   0, 1, 2,
  //   0, 2, 3
  // };

  float vertices[] = {
      // first triangle
       0.5f,  0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f  // top left
  };
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int EBO;
  glGenBuffers(1, &EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  const char *vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "void main()\n"
                                   "{\n"
                                   " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                   "}\0";
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  const char *fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                     "}\0";

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glEnableVertexAttribArray(0);

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.1f, 0.3f, 0.1f, 1.0f);
    // // Render here
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }
  glfwTerminate();
}