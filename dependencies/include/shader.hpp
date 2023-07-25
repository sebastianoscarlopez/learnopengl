#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
  // the program ID
  unsigned int ID;
  // constructor reads and builds the shader
  Shader(const char *vertexPath, const char *fragmentPath);
  // use/activate the shader
  void use(void);
  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setFloatV(const std::string &name, float values[]) const;
  void setFloat4(const std::string &name, float value1, float value2, float value3, float value4) const;
  void setMat4(const std::string &name, GLfloat* values) const;
};
#endif