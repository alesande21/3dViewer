#ifndef OBJECT_H
#define OBJECT_H

#include <QOpenGLFunctions>

#include "../../../Settings/ObjectSettings.h"
#include "../Parser/ParseObject.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include "../Types/s21_Ver2f.h"
#include "../Types/s21_Ver3f.h"
#include "Mesh.h"

namespace s21 {
class Object : protected QOpenGLFunctions {
 public:
  Object() = default;
  void SetSettings(ObjectSettings *settings);
  void UploadObjectFromFile(s21::ParseObject::data_type object);
  void LoadMesh();
  void Draw(Shader &shader_program, Camera &camera, Transformation &model,
            Texture &texture);
  void CleanUp();
  QVector3D ObjectCentre();
  s21::ParseObject::data_type &SendObject();

 private:
  s21::ParseObject::data_type object_;
  ObjectSettings *settings_;
  Mesh mesh_;

 private slots:
  void DrawObject(Shader &shader_program);
  void TypeLine(Shader &shader_program);
  void OffStripple(Shader &shader_program);
};
}  // namespace s21

#endif  // OBJECT_H
