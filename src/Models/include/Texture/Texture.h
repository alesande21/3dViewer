#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions>

#include "../../../Settings/ObjectSettings.h"
#include "../Shader/Shader.h"
#include "SOIL/SOIL.h"

namespace s21 {

class Texture : protected QOpenGLFunctions {
 public:
  Texture() = default;
  void Initialize();
  void Generate();
  void Bind(GLenum target);
  void Unbind(GLenum target);
  void Delete();
  void LoadOrUnload(Shader &shader_id, ObjectSettings *settings);
  void SetData(GLenum target, GLenum texture, std::string filename);
  void SetTex(Shader &shader_id, const char *name);
  void SaveUVMap(const char *filename);

 private:
  GLuint texture_;
  int width_img_{}, height_img_{};
  unsigned char *bytes_;
};
}  // namespace s21

#endif  // TEXTURE_H
