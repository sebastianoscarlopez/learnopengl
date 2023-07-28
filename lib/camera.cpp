#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <camera.hpp>

Camera::Camera(glm::vec3 position)
{
  frontDirection = glm::vec3(0.0f, 0.0f, -1.0f);
  this->position = position;
  this->viewMatrix = glm::lookAt(position, frontDirection, glm::vec3(0, 1, 0));
  this->projectionMatrix = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::moveForward(float speed)
{
  std::cout << glm::to_string(position) << std::endl;
  position += speed * frontDirection;

  std::cout << glm::to_string(position) << std::endl;
  updateViewMatrix();
}

void Camera::moveRight(float speed)
{
  std::cout << glm::to_string(position) << std::endl;
  position += speed * glm::vec3(frontDirection.z, 0.0f, -frontDirection.x);

  std::cout << glm::to_string(position) << std::endl;
  updateViewMatrix();
}

void Camera::rotate(float yawRadians, float pitchRadians) {
  std::cout << "yawRadians: " << yawRadians << " pitchRadians: " << pitchRadians << std::endl;
  glm::vec2 nextDirection = glm::vec2(yawRadians, pitchRadians);
  frontDirection.x = sin(nextDirection.x);
  frontDirection.y = sin(nextDirection.y);
  frontDirection.z = -cos(nextDirection.x) * cos(nextDirection.y);
  
  frontDirection = glm::normalize(frontDirection);
  std::cout << glm::to_string(frontDirection) << std::endl;
  updateViewMatrix();
}

void Camera::updateViewMatrix()
{
  viewMatrix = glm::lookAt(position, position + frontDirection, glm::vec3(0, 1, 0));
}
