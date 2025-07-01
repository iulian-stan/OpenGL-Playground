#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

const static glm::mat4 IDENTITY(1.0f);

class Transformation
{
private:
  glm::mat4 mScale;
  glm::mat4 mTranslate;
  glm::mat4 mRotate;

  glm::mat4 mWTransformation;

public:
  Transformation();

  void Scale(float ScaleX, float ScaleY, float ScaleZ);
  void Translate(float x, float y, float z);
  void Rotate(float RotateX, float RotateY, float RotateZ);

  float* GetWorldTrans();

};

#endif //TRANSFORMATION_H