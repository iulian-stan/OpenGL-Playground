#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

Camera::Camera() : mPosition(0.0f, 0.0f, 0.0f), mFront(0.0f, 0.0f, 1.0f), mUp(0.0f, 1.0f, 0.0f) 
{
  updateVectors();
}

void Camera::OnKeyboard(int key)
{
  switch (key)
  {
  case 101: //GLUT_KEY_UP
    mPosition += mFront * VELOCITY;
    break;

  case 103: //GLUT_KEY_DOWN
    mPosition -= mFront * VELOCITY;
    break;

  case 100: //GLUT_KEY_LEFT
    mPosition -= mRight * VELOCITY;
    break;

  case 102: //GLUT_KEY_RIGHT
    mPosition += mRight * VELOCITY;
    break;

  case 104: //GLUT_KEY_PAGE_UP
    mPosition += mUp * VELOCITY;
    break;

  case 105: //GLUT_KEY_PAGE_DOWN
    mPosition -= mUp * VELOCITY;
    break;

  default:
    break;
  }
}

glm::mat4 Camera::GetCameraTrans()
{
  return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

void Camera::updateVectors()
{
  mRight = glm::normalize(glm::cross(mFront, mUp));
}