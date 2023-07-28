#ifndef CAMERA_FPS_H
#define CAMERA_FPS_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

class CameraFPS {
  public:
    glm::vec3 position;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::vec3 frontDirection;
    glm::vec3 rightDirection;
    glm::vec3 upDirection;
    bool fps;

    CameraFPS(glm::vec3 position, bool fps = false);

    void moveForward(float speed);
    void moveRight(float speed);

    void rotate(float yaw, float pitch);
  private:
    float yawRadians;
    float pitchRadians;
    void updateViewMatrix();
};

#endif
