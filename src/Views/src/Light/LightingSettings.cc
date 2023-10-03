#include "../../include/Light/LightingSettings.h"

#include "ui_lightingsettings.h"

namespace s21 {

LightingSettings::LightingSettings(ObjectSettings &settings, DrawWidget &opengl,
                                   QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::LightingSettings),
      opengl_(&opengl),
      settings_(&settings) {
  ui_->setupUi(this);
  LoadTempSettings();
  connect(ui_->type_carcas, QOverload<bool>::of(&QRadioButton::clicked), this,
          &LightingSettings::ModeCarcass);
  connect(ui_->type_flat, QOverload<bool>::of(&QRadioButton::clicked), this,
          &LightingSettings::ModeFlat);
  connect(ui_->type_smooth, QOverload<bool>::of(&QRadioButton::clicked), this,
          &LightingSettings::ModeSmooth);

  connect(ui_->ambient_light, QOverload<bool>::of(&QRadioButton::clicked), this,
          &LightingSettings::TypeAmbient);
  connect(ui_->specular_light, QOverload<bool>::of(&QRadioButton::clicked),
          this, &LightingSettings::TypeSpecular);

  connect(ui_->color_light_r, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &LightingSettings::LightColor);
  connect(ui_->color_light_g, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &LightingSettings::LightColor);
  connect(ui_->color_light_b, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &LightingSettings::LightColor);

  connect(ui_->light_place_x,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &LightingSettings::LightCoordinate);
  connect(ui_->light_place_y,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &LightingSettings::LightCoordinate);
  connect(ui_->light_place_z,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &LightingSettings::LightCoordinate);

  connect(ui_->ambient_strenght,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &LightingSettings::AmbientStrenght);
  connect(ui_->specular_strenght,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &LightingSettings::SpecularStrenght);
}

LightingSettings::~LightingSettings() { delete ui_; }

void LightingSettings::ModeCarcass() {
  if (settings_->texture_loaded_) {
    settings_->texture_loaded_ = false;
    opengl_->SendController().DeleteTexture();
  }
  settings_->begin_mode_2[0] = 0;
  settings_->begin_mode_2[1] = GL_LINE;
  settings_->begin_mode_2[2] = 0;
  settings_->light_mode_ = 7;
  opengl_->update();
}

void LightingSettings::ModeFlat() {
  settings_->begin_mode_2[0] = 0;
  settings_->begin_mode_2[1] = 0;
  settings_->begin_mode_2[2] = GL_TRIANGLES;
  settings_->light_mode_ = 8;
  opengl_->update();
}

void LightingSettings::ModeSmooth() {
  settings_->begin_mode_2[0] = 0;
  settings_->begin_mode_2[1] = 0;
  settings_->begin_mode_2[2] = GL_TRIANGLES;
  settings_->light_mode_ = 9;
  opengl_->update();
}

void LightingSettings::TypeAmbient() {
  settings_->type_light_ = 10;
  opengl_->update();
}

void LightingSettings::TypeSpecular() {
  settings_->type_light_ = 11;
  opengl_->update();
}

void LightingSettings::LightCoordinate() {
  settings_->light_source_ = {(GLfloat)ui_->light_place_x->value(),
                              (GLfloat)ui_->light_place_y->value(),
                              (GLfloat)ui_->light_place_z->value()};
  opengl_->update();
}

void LightingSettings::LightColor() {
  settings_->light_color_ = {(GLfloat)ui_->color_light_r->value(),
                             (GLfloat)ui_->color_light_g->value(),
                             (GLfloat)ui_->color_light_b->value()};
  opengl_->update();
}

void LightingSettings::AmbientStrenght() {
  settings_->ambient_strenght_ = (GLfloat)ui_->ambient_strenght->value();
  opengl_->update();
}

void LightingSettings::SpecularStrenght() {
  settings_->specular_strenght_ = (GLfloat)ui_->specular_strenght->value();
  opengl_->update();
}

void LightingSettings::LoadTempSettings() {
  ui_->light_place_x->setValue(settings_->light_source_.x());
  ui_->light_place_y->setValue(settings_->light_source_.y());
  ui_->light_place_z->setValue(settings_->light_source_.z());
  ui_->color_light_r->setValue(settings_->light_color_.x());
  ui_->color_light_g->setValue(settings_->light_color_.y());
  ui_->color_light_b->setValue(settings_->light_color_.z());
  ui_->ambient_strenght->setValue(settings_->ambient_strenght_);
  ui_->specular_strenght->setValue(settings_->specular_strenght_);
  if (settings_->type_light_ == 10) ui_->ambient_light->click();
  if (settings_->type_light_ == 11) ui_->specular_light->click();
  if (settings_->light_mode_ == 7) ui_->type_carcas->click();
  if (settings_->light_mode_ == 8) ui_->type_flat->click();
  if (settings_->light_mode_ == 9) ui_->type_smooth->click();
}

}  // namespace s21
