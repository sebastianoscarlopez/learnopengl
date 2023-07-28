#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <camera_fps.hpp>

CameraFPS::CameraFPS(glm::vec3 position, bool fps)
{
  frontDirection = glm::vec3(0.0f, 0.0f, -1.0f);
  this->position = position;
  this->viewMatrix = glm::lookAt(position, frontDirection, glm::vec3(0, 1, 0));
  this->projectionMatrix = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  this->fps = fps;
  this->pitchRadians = 0.0f;
  this->yawRadians = glm::pi<float>() / -2.0f;
}

void CameraFPS::moveForward(float speed)
{
  std::cout << glm::to_string(position) << std::endl;
  position += speed * frontDirection;

  std::cout << glm::to_string(position) << std::endl;
  updateViewMatrix();
}

void CameraFPS::moveRight(float speed)
{
  std::cout << glm::to_string(position) << std::endl;
  position += speed * glm::vec3(frontDirection.z, 0.0f, -frontDirection.x);

  std::cout << glm::to_string(position) << std::endl;
  updateViewMatrix();
}

const float MAX_ANGLE = glm::pi<float>() * 0.2f;
void CameraFPS::rotate(float yawOffset, float pitchOffset)
{
  float nextPitch = pitchRadians + pitchOffset;

  if(fps && nextPitch > MAX_ANGLE ) {
    nextPitch = MAX_ANGLE;
  }
  if(fps && nextPitch < -MAX_ANGLE ) {
    nextPitch = -MAX_ANGLE;
  }
  pitchRadians = nextPitch;
  frontDirection.y = sin(pitchRadians);
  frontDirection.z = cos(pitchRadians) > 0 ? 1.0f : -1.0f;

  float nextYaw = yawRadians + yawOffset;
  yawRadians = nextYaw;

  frontDirection.x = cos(yawRadians);
  frontDirection.z *= sin(yawRadians);

  frontDirection = glm::normalize(frontDirection);
  rightDirection = glm::normalize(glm::cross(frontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
  upDirection = glm::normalize(glm::cross(rightDirection, frontDirection));

  updateViewMatrix();
}

void CameraFPS::updateViewMatrix()
{
  viewMatrix = glm::lookAt(position, position + frontDirection, upDirection);
}
