#include "../../include/Buffers/ElementBufferObject.h"

namespace s21 {

void ElementBufferObject::Generate() {
  initializeOpenGLFunctions();
  glGenBuffers(1, &ebo_);
}

void ElementBufferObject::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
}

void ElementBufferObject::SetData(GLsizeiptr size, GLuint* indices,
                                  GLenum usage) {
  Generate();
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
}

void ElementBufferObject::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void ElementBufferObject::Delete() { glDeleteBuffers(1, &ebo_); }
}  // namespace s21
