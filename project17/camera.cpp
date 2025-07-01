#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "camera.h"

Camera::Camera() : mPosition(0.0f, 0.0f, 0.0f), mFront(0.0f, 0.0f, 1.0f), mUp(0.0f, 1.0f, 0.0f)
{
  mOffsetX = mOffsetY = 0.0f;
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

void Camera::OnMouse(int x, int y)
{
  if (!mIsInit)
  {
    mLastX = x;
    mLastY = y;
    mIsInit = true;
  }

  mOffsetX = mLastX- x;
  mOffsetY = y - mLastY; // reversed since y-coordinates go from bottom to top

  mLastX = x;
  mLastY = y;

  mOffsetX *= MOUSE_SENSITIVITY;
  mOffsetY *= MOUSE_SENSITIVITY;

  // Update Front, Right and Up Vectors using the updated Euler angles
  updateVectors();
}

void Camera::Reset()
{
  mIsInit = false;
}

glm::mat4 Camera::GetCameraTrans()
{
  return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

void Camera::updateVectors()
{
  mFront = glm::rotateY(mFront, glm::radians(mOffsetX));
  mFront = glm::rotateX(mFront, glm::radians(mOffsetY));
  mFront = glm::normalize(mFront);
  mRight = glm::normalize(glm::cross(mFront, mUp));
}