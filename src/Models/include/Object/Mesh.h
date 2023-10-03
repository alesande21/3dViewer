#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../../../Settings/ObjectSettings.h"
#include "../Buffers/ElementBufferObject.h"
#include "../Buffers/VertexArrayObject.h"
#include "../Buffers/VertexBufferObject.h"
#include "../Camera/Camera.h"
#include "../Parser/ParseObject.h"
#include "../Shader/Shader.h"
#include "../Transformation/Transformation.h"
#include "../Types/s21_Ver2f.h"
#include "../Types/s21_Ver3f.h"

namespace s21 {
class Mesh : protected QOpenGLFunctions {
 public:
  Mesh() = default;
  void Initialization(ObjectSettings *settings,
                      s21::ParseObject::data_type &object);
  void Draw(Shader &shader_program, Camera &camera, Transformation &model);
  void EboActivateLines();
  void EboActivateTriangles();
  void EboDeactivateLines();
  void EboDeactivateTriangles();
  void CleanUp();

 private:
  VertexArrayObject va_;
  VertexBufferObject vb_;
  ElementBufferObject eb_lines_;
  ElementBufferObject eb_triangles_;
  ObjectSettings *settings_;
};
}  // namespace s21

#endif  // MESH_H
