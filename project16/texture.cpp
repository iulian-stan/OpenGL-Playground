#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
  mTextureTarget = TextureTarget;
  mFileName = FileName;
}

bool Texture::Load()
{
  int width, height, channels;
  unsigned char *image = stbi_load(mFileName.c_str(), &width, &height, &channels, STBI_rgb_alpha);

  if (!image) {
    return false;
  }

  glGenTextures(1, &mTextureObj);
  glBindTexture(mTextureTarget, mTextureObj);
  glTexImage2D(mTextureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glTexParameterf(mTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(mTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(mTextureTarget, 0);
  stbi_image_free(image);

  return true;
}

void Texture::Bind(GLenum TextureUnit)
{
  glActiveTexture(TextureUnit);
  glBindTexture(mTextureTarget, mTextureObj);
}