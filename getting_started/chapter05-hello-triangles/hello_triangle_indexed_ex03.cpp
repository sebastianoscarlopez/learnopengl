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
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  float vertices_square[] = {
      // square
      0.5f, 0.5f, 0.0f,   // top right
      0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f, 0.0f,  // top left
  };

  unsigned int indices_square[] = {
      // note that we start from 0!
      0, 1, 3, // first triangle square
      1, 2, 3  // second triangle square
  };

  unsigned int vao_square;
  glGenVertexArrays(1, &vao_square);
  glBindVertexArray(vao_square);

  unsigned int vbo_square;
  glGenBuffers(1, &vbo_square);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_square);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_square), vertices_square, GL_STATIC_DRAW);

  unsigned int ebo_square;
  glGenBuffers(1, &ebo_square);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_square);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_square), indices_square, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  float vertices_triangles[] = {
      // square
      0.5f, 0.5f, 0.0f,  // triangle R bottom right
      -0.5f, 0.5f, 0.0f, // triangle L bottom left
      0.0, 0.5, 0.0f,    // triangles bottom middle
      -0.25, 0.75, 0.0f, // triangle L top
      0.25, 0.75, 0.0f   // triangle R top
  };

  unsigned int indices_triangles[] = {
      // note that we start from 0!
      2, 1, 3, // triangle L
      0, 2, 4, // triangle R
  };

  unsigned int vao_triangles;
  glGenVertexArrays(1, &vao_triangles);
  glBindVertexArray(vao_triangles);

  unsigned int vbo_triangles;
  glGenBuffers(1, &vbo_triangles);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangles);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangles), vertices_triangles, GL_STATIC_DRAW);

  unsigned int ebo_triangles;
  glGenBuffers(1, &ebo_triangles);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_triangles);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_triangles), indices_triangles, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

  const char *fragShaderYellowSource = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     " FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                     "}\0";

  unsigned int fragmentShaderYellow;
  fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderYellow, 1, &fragShaderYellowSource, NULL);
  glCompileShader(fragmentShaderYellow);

  unsigned int shaderProgramYellow;
  shaderProgramYellow = glCreateProgram();
  glAttachShader(shaderProgramYellow, vertexShader);
  glAttachShader(shaderProgramYellow, fragmentShaderYellow);
  glLinkProgram(shaderProgramYellow);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShaderYellow);


  const char *fragShaderBlueSource = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     " FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
                                     "}\0";

  unsigned int fragmentShaderBlue;
  fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderBlue, 1, &fragShaderBlueSource, NULL);
  glCompileShader(fragmentShaderBlue);

  unsigned int shaderProgramBlue;
  shaderProgramBlue = glCreateProgram();
  glAttachShader(shaderProgramBlue, vertexShader);
  glAttachShader(shaderProgramBlue, fragmentShaderBlue);
  glLinkProgram(shaderProgramBlue);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShaderBlue);


  // glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glBindVertexArray(vao_square);
  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.1f, 0.3f, 0.1f, 1.0f);
    // // Render here
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgramYellow);

    glBindVertexArray(vao_square);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glUseProgram(shaderProgramBlue);
    glBindVertexArray(vao_triangles);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }
  glfwTerminate();
}