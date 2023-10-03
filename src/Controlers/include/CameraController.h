#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QVector3D>

#include "../../Models/include/Camera/Camera.h"
#include "../../Models/include/Point/FocusPoint.h"
#include "../../Settings/ObjectSettings.h"

namespace s21 {
class CameraController {
 public:
  CameraController();
  void LoadCameraSettings(int width, int height, QVector3D position,
                          ObjectSettings *settings);
  void UpdateCamera(float vertical_angle, float nearPlane, float far_plane);
  bool UpdateScale(int y);
  void UpdateMoving(QPoint pos_new, QPoint pos_old);
  void Resize(int width, int height);
  void Zoom(float prev, float curr);
  void FreeMoveX(float prev, float curr);
  void FreeMoveY(float prev, float curr);
  void FreeMoveZ(float prev, float curr);
  void MoreSpeed();
  void LessSpeed();
  Camera &GetCamera();

 private:
  Camera *camera_;
};
}  // namespace s21

#endif  // CAMERACONTROLLER_H
