#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

const static float VELOCITY = 0.2f;
const static float MOUSE_SENSITIVITY = 0.02f;

class Camera {
private:
  glm::vec3 mPosition;
  glm::vec3 mFront;
  glm::vec3 mUp;
  glm::vec3 mRight;
  bool mIsInit = false;
  int mLastX, mLastY;
  float mOffsetX, mOffsetY;

public:
  Camera();

  void OnKeyboard(int key);
  void OnMouse(int x, int y);

  void Reset();

  glm::mat4 GetCameraTrans();

private:
  void updateVectors();
};

#endif //CAMERA_H