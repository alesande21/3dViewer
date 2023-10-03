#include "../../include/Transformation/ParamTransform.h"

#include "ui_paramtransform.h"

namespace s21 {

ParamTransform::ParamTransform(DrawWidget &opengl, QWidget *parent)
    : QWidget(parent), ui_(new Ui::ParamTransform), opengl_(&opengl) {
  ui_->setupUi(this);
  LoadTempSettings();
  connect(ui_->rot_x, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &ParamTransform::RotX);
  connect(ui_->rot_y, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &ParamTransform::RotY);
  connect(ui_->rot_z, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &ParamTransform::RotZ);

  connect(ui_->trans_x, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &ParamTransform::TransX);
  connect(ui_->trans_y, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &ParamTransform::TransY);
  connect(ui_->trans_z, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &ParamTransform::TransZ);

  connect(ui_->scale, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &ParamTransform::Scale);
}

ParamTransform::~ParamTransform() {
  SaveTempSettings();
  delete ui_;
}

void ParamTransform::RotX() {
  static float prev = 0;
  opengl_->SendController().RotationX(prev, ui_->rot_x->value());
  prev = ui_->rot_x->value();
  opengl_->update();
}

void ParamTransform::RotY() {
  static float prev = 0;
  opengl_->SendController().RotationY(prev, ui_->rot_y->value());
  prev = ui_->rot_y->value();
  opengl_->update();
}

void ParamTransform::RotZ() {
  static float prev = 0;
  opengl_->SendController().RotationZ(prev, ui_->rot_z->value());
  prev = ui_->rot_z->value();
  opengl_->update();
}

void ParamTransform::TransX() {
  static float prev = 0;
  opengl_->SendController().TranslateX(prev, ui_->trans_x->value());
  prev = ui_->trans_x->value();
  opengl_->update();
}

void ParamTransform::TransY() {
  static float prev = 0;
  opengl_->SendController().TranslateY(prev, ui_->trans_y->value());
  prev = ui_->trans_y->value();
  opengl_->update();
}

void ParamTransform::TransZ() {
  static float prev = 0;
  opengl_->SendController().TranslateZ(prev, ui_->trans_z->value());
  prev = ui_->trans_z->value();
  opengl_->update();
}

void ParamTransform::Scale() {
  static float prev = 0;
  opengl_->SendController().Scale(prev, ui_->scale->value());
  prev = ui_->scale->value();
  opengl_->update();
}

void ParamTransform::LoadTempSettings() {
  QSettings qsettings("temp_trans_settings.ini", QSettings::IniFormat);
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

void ParamTransform::SaveTempSettings() {
  QSettings qsettings("temp_trans_settings.ini", QSettings::IniFormat);
  qsettings.setValue("trans",
                     QVector3D(ui_->trans_x->value(), ui_->trans_y->value(),
                               ui_->trans_z->value()));
  qsettings.setValue("rot", QVector3D(ui_->rot_x->value(), ui_->rot_y->value(),
                                      ui_->rot_z->value()));
  qsettings.setValue("scale", ui_->scale->value());
}

}  // namespace s21
