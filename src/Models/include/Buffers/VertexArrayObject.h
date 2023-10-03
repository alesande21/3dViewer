#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>

namespace s21 {
class VertexArrayObject : public QOpenGLExtraFunctions {
 public:
  VertexArrayObject() = default;
  void Generate();
  void Bind();
  void Unbind();
  void Delete();

 private:
  GLuint vao_;
};
}  // namespace s21

#endif  // VERTEXARRAYOBJECT_H
