#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

namespace s21 {
class VertexBufferObject : protected QOpenGLFunctions {
 public:
  VertexBufferObject() = default;
  void LinkVertexAttribute(GLuint index, GLint size, GLenum type,
                           GLboolean normalized, GLsizeiptr stride,
                           const GLvoid* pointer);
  void Bind();
  void SetData(GLsizeiptr size, const GLvoid* vertices, GLenum usage);
  void ConfigureVertexAttribute(GLuint index, GLint size, GLenum type,
                                GLboolean normalized, GLsizeiptr stride,
                                const GLvoid* pointer);
  void Unbind();
  void Delete();

 private:
  GLuint vbo_;

 private slots:
  void Generate();
};
}  // namespace s21

#endif  // VERTEXBUFFEROBJECT_H
