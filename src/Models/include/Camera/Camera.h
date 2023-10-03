#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QQuaternion>
#include <QTransform>
#include <QVector3D>
#include <QtGui/QKeyEvent>
#include <QtMath>

#include "../../../Settings/ObjectSettings.h"
#include "../Shader/Shader.h"

namespace s21 {
class Camera : protected QOpenGLFunctions {
 public:
  void Initialization(int width, int height, QVector3D position,
                      ObjectSettings *settings);
  void UpdateMatrix(float vertical_angle, float nearPlane, float far_plane);
  void Matrix(Shader &shader_program, const char *name);
  bool Input(float delta);
  //  void Input(float x, float y);
  void Input(QVector2D cur_pos);
  void Resize(int width, int height);
  void FreeMoveX(float sign);
  void FreeMoveY(float sign);
  void FreeMoveZ(float sign);
  void MoreSpeed();
  void LessSpeed();
  void CalcFocusPos();
  QVector3D GetPosition();
  static Camera &GetInstance();

 private:
  int width_{};
  int height_{};
  float scale_ = 1.0f;
  float speed_ = 0.04f;
  float sensitivity_ = 20.0f;
  QVector3D up_ = {0.0f, 1.0f, 0.0f};
  QPoint old_pos_{};
  QVector3D position_{};
  QVector3D translate_{};
  QVector3D orientation_ = {0.0f, 0.0f, -1.0f};
  QVector3D focus_rotation_{};
  QMatrix4x4 camera_matrix_{};
  ObjectSettings *settings_;

  Camera() = default;
  Camera(const Camera &) = delete;
  Camera &operator=(const Camera &) = delete;
};
}  // namespace s21

#endif  // CAMERA_H
