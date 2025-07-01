#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
private:
  glm::vec3 mPosition;
  glm::vec3 mFront;
  glm::vec3 mUp;

public:
  Camera();
  Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);

  glm::mat4 GetCameraTrans();
};

#endif //CAMERA_H