// #ifndef SHADER_H
// #define SHADER_H
// #endif

#include <glad/glad.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <shader.hpp>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{

  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try
  {
    // open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file?s buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure e)
  {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  // const char *vShaderCode = "#version 330 core\n"
  //                           "layout (location = 0) in vec3 aPos;\n"
  //                           "void main()\n"
  //                           "{\n"
  //                           " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  //                           "}\0";
  // const char *fShaderCode = "#version 330 core\n"
  //                           "out vec4 FragColor;\n"
  //                           "void main()\n"
  //                           "{\n"
  //                           " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  //                           "}\0";

  // 2. compile shaders
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  };
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  // print compile errors if any
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  };

#ifdef __DEBUG
  std::cout << "vertex" << std::endl;
  std::cout << vShaderCode << std::endl;
  std::cout << "fragment" << std::endl;
  std::cout << fShaderCode << std::endl;
#endif

  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  // print linking errors if any
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  // delete shaders; they?re linked into our program and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
};

void Shader::use()
{
  glUseProgram(ID);
};
void Shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat4(const std::string &name, float value1, float value2, float value3, float value4) const
{
  glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value3, value3, value4);
}
void Shader::setFloatV(const std::string &name, float values[]) const
{
  glUniform4f(glGetUniformLocation(ID, name.c_str()), values[0], values[1], values[2], values[3]);
}
void Shader::setMat4(const std::string &name, GLfloat* values) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, values);
}