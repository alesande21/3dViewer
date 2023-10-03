#include "../../include/Buffers/VertexBufferObject.h"

namespace s21 {

void VertexBufferObject::Generate() {
  initializeOpenGLFunctions();
  glGenBuffers(1, &vbo_);
}

void VertexBufferObject::Bind() { glBindBuffer(GL_ARRAY_BUFFER, vbo_); }

void VertexBufferObject::SetData(GLsizeiptr size, const GLvoid* vertices,
                                 GLenum usage) {
  Generate();
  Bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
}

void VertexBufferObject::ConfigureVertexAttribute(GLuint index, GLint size,
                                                  GLenum type,
                                                  GLboolean normalized,
                                                  GLsizeiptr stride,
                                                  const GLvoid* pointer) {
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  glEnableVertexAttribArray(index);
}

void VertexBufferObject::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBufferObject::Delete() { glDeleteBuffers(1, &vbo_); }

void VertexBufferObject::LinkVertexAttribute(GLuint index, GLint size,
                                             GLenum type, GLboolean normalized,
                                             GLsizeiptr stride,
                                             const GLvoid* pointer) {
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  glEnableVertexAttribArray(index);
}

}  // namespace s21
