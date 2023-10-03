#ifndef FOCUSPOINT_H
#define FOCUSPOINT_H

#include <QOpenGLFunctions>

#include "../../../Settings/ObjectSettings.h"
#include "../Buffers/ElementBufferObject.h"
#include "../Buffers/VertexArrayObject.h"
#include "../Buffers/VertexBufferObject.h"
#include "../Camera/Camera.h"
#include "../Object/Mesh.h"
#include "../Shader/Shader.h"
#include "../Transformation/Transformation.h"

namespace s21 {
class FocusPoint : protected QOpenGLFunctions {
 public:
  FocusPoint() = default;
  void SetSettings(ObjectSettings *settings);
  void UpdatePoint(Camera &camera, std::vector<GLuint> ind,
                   QVector3D color_vertex, GLint size_point);
  void LoadPoint(std::vector<GLfloat> vert, std::vector<GLuint> ind);
  void LoadShader();
  void UpdateTransform(QVector3D new_pos);

 private:
  ObjectSettings *settings_;
  Shader shader_program_point_;
  VertexArrayObject va_;
  VertexBufferObject vb_;
  ElementBufferObject eb_;
  Transformation tr_;
};
}  // namespace s21

#endif  // FOCUSPOINT_H
