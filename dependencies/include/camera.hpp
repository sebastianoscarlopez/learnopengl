#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera {
  public:
    glm::vec3 position;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::vec3 frontDirection;

    Camera(glm::vec3 position);

    void moveForward(float speed);
    void moveRight(float speed);

    void rotate(float yaw, float pitch);
  private:
    void updateViewMatrix();
};

#endif
