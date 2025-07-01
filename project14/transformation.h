#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "camera.h"

const static glm::mat4 IDENTITY(1.0f);

struct PerspectiveProjection
{
  float FOV;
  float Width;
  float Height;
  float zNear;
  float zFar;
};

class Transformation
{
private:
  glm::mat4 mScale;
  glm::mat4 mTranslate;
  glm::mat4 mRotate;
  glm::mat4 mPersProj;

  Camera* mCamera;

  glm::mat4 mWTransformation;
  glm::mat4 mWPTransformation;

public:
  Transformation();

  void Scale(float ScaleX, float ScaleY, float ScaleZ);
  void Translate(float x, float y, float z);
  void Rotate(float RotateX, float RotateY, float RotateZ);

  void SetPerspectiveProj(const PerspectiveProjection& p);
  void SetCamera(Camera* c);

  float* GetWorldTrans();
  float* GetWPTrans();
  float* GetWVPTrans();

};

#endif //TRANSFORMATION_H