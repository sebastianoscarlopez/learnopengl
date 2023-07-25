#ifndef SQUARE_H
#define SQUARE_H
#include <shapes/shape.hpp>

class Square : public Shape
{
public:

  const char *vertexPath = "./shaders/chapter09/square.vs";
  const char *fragmentPath = "./shaders/chapter09/square.fs";

  Square();

  void use();

  void draw();

protected:
  unsigned int VAO;
  unsigned int texture0, texture1;
  void configure();
};
#endif