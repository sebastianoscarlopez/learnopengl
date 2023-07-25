#include <iostream>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/string_cast.hpp>

#include <shader.hpp>

using namespace std;

int main()
{
  // This is the default projection matrix. Identity matrix.
  // Think of it as a 3D box that goes from -1 to 1 in all directions.
  // The camera is at 0, 0, 1 looking at 0, 0, 0.
  glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f);
  std::cout << glm::to_string(projection) << std::endl;

  // Orthography projection with NDC 800x600x.
  // Think of it as a 3D box that goes from -1 to 1 in all directions.
  // The camera is at 0, 0, 1 looking at 0, 0, 0.
  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 1.0f, -1.0f);
  std::cout << glm::to_string(projection) << std::endl;
}