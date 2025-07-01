#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <GL/glew.h>

class Texture
{
public:
  Texture(GLenum TextureTarget, const std::string& FileName);

  bool Load();

  void Bind(GLenum TextureUnit);

private:
  std::string mFileName;
  GLenum mTextureTarget;
  GLuint mTextureObj;
};

#endif //TEXTURE_H