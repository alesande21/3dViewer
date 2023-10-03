#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <QOpenGLFunctions>
#include <QtGui/QKeyEvent>

#include "../Shader/Shader.h"

namespace s21 {
class Transformation : protected QOpenGLFunctions {
 public:
  Transformation() = default;
  void Initialization();
  void Matrix(Shader &shader_program, const char *name);
  void Translate(float x, float y, float z);
  void Rotation(float angle, float x, float y, float z);
  void Scale(float x, float y, float z);

 private:
  QMatrix4x4 transform_;
};
}  // namespace s21

#endif  // TRANSFORMATION_H
