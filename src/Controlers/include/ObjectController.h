#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <QDir>
#include <QtGui/QKeyEvent>

#include "../../Models/include/Camera/Camera.h"
#include "../../Models/include/Object/Object.h"
#include "../../Models/include/Parser/ParseObject.h"
#include "../../Models/include/Point/FocusPoint.h"
#include "../../Models/include/Shader/Shader.h"
#include "../../Models/include/Texture/Texture.h"
#include "../../Models/include/Transformation/Transformation.h"
#include "../../Models/include/Types/s21_Fac3f.h"
#include "../../Models/include/Types/s21_Ver2f.h"
#include "../../Models/include/Types/s21_Ver3f.h"
#include "../../Settings/ObjectSettings.h"

namespace s21 {
class ObjectController : protected QOpenGLFunctions {
 public:
  ObjectController() = default;
  ~ObjectController();
  void Initialize(ObjectSettings *settings_);
  void UploadObjectFromFile(const std::string &filepath);
  void LoadPoint(ObjectSettings *settings);
  void DrawPoint(ObjectSettings *settings, Camera &camera);
  void LoadShader();
  void InitializeTexture();
  void UpdateTexture(QString path_to_texture);
  void DeleteTexture();
  void DrawObject(Camera &camera);
  void RotationX(float prev, float curr);
  void RotationY(float prev, float curr);
  void RotationZ(float prev, float curr);
  void TranslateX(float prev, float curr);
  void TranslateY(float prev, float curr);
  void TranslateZ(float prev, float curr);
  void Scale(float prev, float curr);
  void SaveUvMap(const char *filename);
  void CleanUp();
  s21::ParseObject::data_type GetObject();

 private:
  Object object_;
  Texture texture_;
  QString current_path_;
  Shader shader_program_;
  FocusPoint point_light_;
  FocusPoint point_centre_;
  s21::ParseObject parser_;
  ObjectSettings *settings_;
  Transformation transformation_;
};
}  // namespace s21

#endif  // OBJECTCONTROLLER_H
