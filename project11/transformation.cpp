#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "transformation.h"

Transformation::Transformation() : mScale(IDENTITY), mTranslate(IDENTITY), mRotate(IDENTITY)
{
}

void Transformation::Scale(float ScaleX, float ScaleY, float ScaleZ) 
{
  mScale = glm::scale(IDENTITY, glm::vec3(ScaleX, ScaleY, ScaleZ));
}

void Transformation::Translate(float x, float y, float z)
{
  mTranslate = glm::translate(IDENTITY, glm::vec3(x, y, z));
}

void Transformation::Rotate(float RotateX, float RotateY, float RotateZ)
{
  mRotate = glm::eulerAngleXYZ(glm::radians(RotateX), glm::radians(RotateY), glm::radians(RotateZ));
}

float* Transformation::GetWorldTrans()
{
  mWTransformation = mTranslate * mRotate * mScale;
  return glm::value_ptr(mWTransformation);
}