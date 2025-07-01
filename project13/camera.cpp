#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

Camera::Camera() : mPosition(0.0f, 0.0f, 0.0f), mFront(0.0f, 0.0f, 1.0f), mUp(0.0f, 1.0f, 0.0f) 
{
}

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up) : mPosition(position), mFront(front), mUp(up)
{
}

glm::mat4 Camera::GetCameraTrans()
{
  return glm::lookAt(mPosition, mPosition + mFront, mUp);
}