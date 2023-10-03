#ifndef CAMERASETTING_H
#define CAMERASETTING_H

#include <QOpenGLFunctions>
#include <QWidget>

#include "../../../Controlers/include/CameraController.h"
#include "../../../Settings/ObjectSettings.h"
#include "../Draw/DrawWidget.h"

namespace Ui {
class CameraSetting;
}

namespace s21 {
class CameraSetting : public QWidget {
  Q_OBJECT

 public:
  explicit CameraSetting(ObjectSettings &settings, DrawWidget &opengl,
                         QWidget *parent = nullptr);
  ~CameraSetting();

 private:
  Ui::CameraSetting *ui_;
  DrawWidget *opengl_;
  ObjectSettings *settings_;

 private slots:
  void Zoom();
  void RotX();
  void RotY();
  void RotZ();
  void TransX();
  void TransY();
  void TransZ();
  void CameraFree();
  void CameraFocus();
  void ProjectionsParallel();
  void ProjectionsPerspectiv();
  void Fov();
  void FarPlane();
  void NearPlane();
  void LoadSettings();
  void SaveTempSettings();
  void LoadTempSettings();
};
}  // namespace s21

#endif  // CAMERASETTING_H
