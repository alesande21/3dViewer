#include "../../include/Transformation/Transformation.h"

namespace s21 {

void Transformation::Initialization() { initializeOpenGLFunctions(); }

void Transformation::Matrix(Shader &shader_program, const char *name) {
  int location_model = glGetUniformLocation(shader_program.GetShaderId(), name);
  glUniformMatrix4fv(location_model, 1, GL_FALSE, transform_.constData());
}

void Transformation::Translate(float x, float y, float z) {
  transform_.translate(x, y, z);
}

void Transformation::Rotation(float angle, float x, float y, float z) {
  transform_.rotate(angle, {x, y, z});
}

void Transformation::Scale(float x, float y, float z) {
  transform_.scale(x, y, z);
}

}  // namespace s21
