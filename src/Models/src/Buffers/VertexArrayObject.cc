#include "../../include/Buffers/VertexArrayObject.h"

#include <iostream>

namespace s21 {
void VertexArrayObject::Generate() {
  initializeOpenGLFunctions();
  glGenVertexArrays(1, &vao_);
}

void VertexArrayObject::Bind() { glBindVertexArray(vao_); }

void VertexArrayObject::Unbind() { glBindVertexArray(0); }

void VertexArrayObject::Delete() { glDeleteVertexArrays(1, &vao_); }
}  // namespace s21
