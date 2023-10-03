#include "../../include/Camera/CameraSetting.h"

#include "ui_camerasetting.h"

namespace s21 {

CameraSetting::CameraSetting(ObjectSettings &settings, DrawWidget &opengl,
                             QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::CameraSetting),
      opengl_(&opengl),
      settings_(&settings) {
  ui_->setupUi(this);

  LoadSettings();
  LoadTempSettings();
  connect(ui_->rot_x, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &CameraSetting::RotX);
  connect(ui_->rot_y, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &CameraSetting::RotY);
  connect(ui_->rot_z, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &CameraSetting::RotZ);

  connect(ui_->trans_x, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &CameraSetting::TransX);
  connect(ui_->trans_y, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &CameraSetting::TransY);
  connect(ui_->trans_z, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &CameraSetting::TransZ);

  connect(ui_->scale, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &CameraSetting::Zoom);

  connect(ui_->free, QOverload<bool>::of(&QRadioButton::clicked), this,
          &CameraSetting::CameraFree);

  connect(ui_->focus, QOverload<bool>::of(&QRadioButton::clicked), this,
          &CameraSetting::CameraFocus);

  connect(ui_->paral, QOverload<bool>::of(&QRadioButton::clicked), this,
          &CameraSetting::ProjectionsParallel);
  connect(ui_->persp, QOverload<bool>::of(&QRadioButton::clicked), this,
          &CameraSetting::ProjectionsPerspectiv);

  connect(ui_->far_plane, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &CameraSetting::FarPlane);
  connect(ui_->near_plane, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &CameraSetting::NearPlane);
  connect(ui_->fov, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &CameraSetting::Fov);
}

CameraSetting::~CameraSetting() {
  SaveTempSettings();
  delete ui_;
}

void CameraSetting::Zoom() {
  static float prev = 0;
  opengl_->SendCameraController().Zoom(prev, ui_->scale->value());
  prev = ui_->scale->value();
  opengl_->update();
}

void CameraSetting::RotX() {
  static int prev = 0;
  opengl_->SendCameraController().UpdateMoving({(int)(ui_->rot_x->value()), 0},
                                               {prev, 0});
  prev = ui_->rot_x->value();
  opengl_->update();
}

void CameraSetting::RotY() {
  static int prev = 0;
  opengl_->SendCameraController().UpdateMoving({0, (int)(ui_->rot_y->value())},
                                               {0, prev});
  prev = ui_->rot_y->value();
  opengl_->update();
}

void CameraSetting::RotZ() {
  static int prev = 0;
  int rotationAngle = 10;
  opengl_->SendCameraController().UpdateMoving({0, 0},
                                               {0, prev + rotationAngle});
  prev += rotationAngle;
  opengl_->update();
}

void CameraSetting::TransX() {
  static float prev = 0;
  opengl_->SendCameraController().FreeMoveX(prev, ui_->trans_x->value());
  prev = ui_->trans_x->value();
  opengl_->update();
}

void CameraSetting::TransY() {
  static float prev = 0;
  opengl_->SendCameraController().FreeMoveY(prev, ui_->trans_y->value());
  prev = ui_->trans_y->value();
  opengl_->update();
}

void CameraSetting::TransZ() {
  static float prev = 0;
  opengl_->SendCameraController().FreeMoveZ(prev, ui_->trans_z->value());
  prev = ui_->trans_z->value();
  opengl_->update();
}

void CameraSetting::CameraFree() {
  settings_->type_camera_ = FREE;
  opengl_->update();
}

void CameraSetting::CameraFocus() {
  settings_->type_camera_ = FOCUS;
  opengl_->update();
}

void CameraSetting::ProjectionsParallel() {
  settings_->type_projections_ = PARALLEL;
  opengl_->update();
}

void CameraSetting::ProjectionsPerspectiv() {
  settings_->type_projections_ = PERSPECTIVE;
  opengl_->update();
}

void CameraSetting::Fov() {
  settings_->fov_ = ui_->fov->value();
  opengl_->update();
}

void CameraSetting::FarPlane() {
  settings_->far_plane_ = ui_->far_plane->value();
  opengl_->update();
}

void CameraSetting::NearPlane() {
  settings_->near_plane_ = ui_->near_plane->value();
  opengl_->update();
}

void CameraSetting::LoadSettings() {
  if (settings_->type_projections_ == PERSPECTIVE) ui_->persp->click();
  if (settings_->type_projections_ == PARALLEL) ui_->paral->click();
}

void CameraSetting::SaveTempSettings() {
  QSettings qsettings("temp_camera_settings.ini", QSettings::IniFormat);
  qsettings.setValue("trans",
                     QVector3D(ui_->trans_x->value(), ui_->trans_y->value(),
                               ui_->trans_z->value()));
  qsettings.setValue("rot", QVector3D(ui_->rot_x->value(), ui_->rot_y->value(),
                                      ui_->rot_z->value()));
  qsettings.setValue("scale", ui_->scale->value());
}

void CameraSetting::LoadTempSettings() {
  ui_->near_plane->setValue(settings_->near_plane_);
  ui_->far_plane->setValue(settings_->far_plane_);
  ui_->fov->setValue(settings_->fov_);
  if (settings_->type_camera_ == FOCUS) ui_->focus->click();
  if (settings_->type_camera_ == FREE) ui_->free->click();
  QSettings qsettings("temp_camera_settings.ini", QSettings::IniFormat);
  QVector3D temp{};
  temp =
      qsettings.value("trans", QVector3D(0.0f, 0.0f, 0.0f)).value<QVector3D>();
  ui_->trans_x->setValue(temp.x());
  ui_->trans_y->setValue(temp.y());
  ui_->trans_z->setValue(temp.z());
  temp = qsettings.value("rot", QVector3D(0.0f, 0.0f, 0.0f)).value<QVector3D>();
  ui_->rot_x->setValue(temp.x());
  ui_->rot_y->setValue(temp.y());
  ui_->rot_z->setValue(temp.z());
  auto scale = qsettings.value("scale", 0).value<GLfloat>();
  ui_->scale->setValue(scale);
}

}  // namespace s21
