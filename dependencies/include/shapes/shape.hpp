#ifndef SHAPE_H
#define SHAPE_H
#include <shader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shape
{
public:
  Shader *shaderProgram;

  glm::mat4 modelMatrix = glm::mat4(1.0f);

  virtual void use() = 0;

  virtual void draw() = 0;

protected:
  virtual void configure() = 0;
};
#endif