#include <stb_image.h>
#include <shapes/box.hpp>
#include <shader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void Box::draw()
{
  // Top face
  glm::mat4 auxFaceMatrix(modelMatrix);
  auxFaceMatrix = glm::translate(auxFaceMatrix, glm::vec3(0.0, 0.5, 0.0));
  auxFaceMatrix = glm::rotate(auxFaceMatrix, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
  shaderProgram->setMat4("modelMatrix", glm::value_ptr(auxFaceMatrix));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Bottom face
  auxFaceMatrix = glm::translate(modelMatrix, glm::vec3(0.0, -0.5, 0.0));
  auxFaceMatrix = glm::rotate(auxFaceMatrix, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
  shaderProgram->setMat4("modelMatrix", glm::value_ptr(auxFaceMatrix));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Left face
  auxFaceMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, 0.0, 0.0));
  auxFaceMatrix = glm::rotate(auxFaceMatrix, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));
  shaderProgram->setMat4("modelMatrix", glm::value_ptr(auxFaceMatrix));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Right face
  auxFaceMatrix = glm::translate(modelMatrix, glm::vec3(0.5, 0.0, 0.0));
  auxFaceMatrix = glm::rotate(auxFaceMatrix, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
  shaderProgram->setMat4("modelMatrix", glm::value_ptr(auxFaceMatrix));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Back face
  auxFaceMatrix = glm::translate(modelMatrix, glm::vec3(0.0, 0.0, -0.5));
  auxFaceMatrix = glm::rotate(auxFaceMatrix, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
  shaderProgram->setMat4("modelMatrix", glm::value_ptr(auxFaceMatrix));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Front face
  auxFaceMatrix = glm::translate(modelMatrix, glm::vec3(0.0, 0.0, 0.5));
  auxFaceMatrix = glm::rotate(auxFaceMatrix, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
  shaderProgram->setMat4("modelMatrix", glm::value_ptr(auxFaceMatrix));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}