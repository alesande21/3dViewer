#ifndef ELEMENTBUFFEROBJECT_H
#define ELEMENTBUFFEROBJECT_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

namespace s21 {
class ElementBufferObject : protected QOpenGLFunctions {
 public:
  ElementBufferObject() = default;
  void Generate();
  void Bind();
  void SetData(GLsizeiptr size, GLuint* indices, GLenum usage);
  void Unbind();
  void Delete();

 private:
  GLuint ebo_;
};

}  // namespace s21

#endif  // ELEMENTBUFFEROBJECT_H
