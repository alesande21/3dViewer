#include "../../include/Color/Color.h"

#include "ui_color.h"

namespace s21 {

Color::Color(ObjectSettings &settings, DrawWidget &scene, QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::Color),
      scene_(&scene),
      settings_(&settings) {
  ui_->setupUi(this);
  LoadSettings();
  connect(ui_->color_back_r, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorBack);
  connect(ui_->color_back_g, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorBack);
  connect(ui_->color_back_b, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorBack);

  connect(ui_->exterior_r, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorExterior);
  connect(ui_->exterior_g, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorExterior);
  connect(ui_->exterior_b, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorExterior);

  connect(ui_->color_line_r, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorLine);
  connect(ui_->color_line_g, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorLine);
  connect(ui_->color_line_b, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorLine);

  connect(ui_->color_ver_r, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorVertex);
  connect(ui_->color_ver_g, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorVertex);
  connect(ui_->color_ver_b, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::ColorVertex);

  connect(ui_->size_vertex, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::SizeVertex);

  connect(ui_->line_width, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &Color::WidthLine);

  connect(ui_->type_line_1, QOverload<bool>::of(&QRadioButton::clicked), this,
          &Color::LineModeSolid);
  connect(ui_->type_line_2, QOverload<bool>::of(&QRadioButton::clicked), this,
          &Color::LineModeStripple);

  connect(ui_->type_vert_nope, QOverload<bool>::of(&QRadioButton::clicked),
          this, &Color::VertexModeNope);
  connect(ui_->type_vert_sq, QOverload<bool>::of(&QRadioButton::clicked), this,
          &Color::VertexModeSquare);
  connect(ui_->type_vert_round, QOverload<bool>::of(&QRadioButton::clicked),
          this, &Color::VertexModeRound);

  connect(ui_->point, QOverload<bool>::of(&QRadioButton::clicked), this,
          &Color::Primitive);
  connect(ui_->line, QOverload<bool>::of(&QRadioButton::clicked), this,
          &Color::Primitive);
  connect(ui_->triangle, QOverload<bool>::of(&QRadioButton::clicked), this,
          &Color::Primitive);
  connect(ui_->resetColor, QOverload<bool>::of(&QPushButton::clicked), this,
          &Color::ResetSettings);
}

Color::~Color() { delete ui_; }

void Color::ColorBack() {
  settings_->color_back_ = {(GLfloat)ui_->color_back_r->value(),
                            (GLfloat)ui_->color_back_g->value(),
                            (GLfloat)ui_->color_back_b->value()};
  scene_->update();
}

void Color::ColorLine() {
  settings_->color_line_ = {(GLfloat)ui_->color_line_r->value(),
                            (GLfloat)ui_->color_line_g->value(),
                            (GLfloat)ui_->color_line_b->value()};
  scene_->update();
}

void Color::ColorVertex() {
  settings_->color_vertex_ = {(GLfloat)ui_->color_ver_r->value(),
                              (GLfloat)ui_->color_ver_g->value(),
                              (GLfloat)ui_->color_ver_b->value()};
  scene_->update();
}

void Color::ColorExterior() {
  settings_->color_exterior_ = {(GLfloat)ui_->exterior_r->value(),
                                (GLfloat)ui_->exterior_g->value(),
                                (GLfloat)ui_->exterior_b->value()};
  scene_->update();
}

void Color::SizeVertex() {
  settings_->size_vertex_ = (GLint)ui_->size_vertex->value();
  scene_->update();
}

void Color::WidthLine() {
  settings_->width_line_ = (GLint)ui_->line_width->value();
  scene_->update();
}

void Color::LineModeSolid() {
  settings_->line_mode_ = GL_LINE;
  scene_->update();
}

void Color::LineModeStripple() {
  settings_->line_mode_ = GL_LINE_STIPPLE;
  scene_->update();
}

void Color::VertexModeNope() {
  settings_->vertex_mode_ = 0;
  scene_->update();
}

void Color::VertexModeRound() {
  settings_->vertex_mode_ = 2;
  scene_->update();
}

void Color::VertexModeSquare() {
  settings_->vertex_mode_ = 1;
  scene_->update();
}

void Color::Primitive() {
  std::memset(settings_->begin_mode_2, 0, sizeof(settings_->begin_mode_2));
  if (ui_->point->isChecked()) settings_->begin_mode_2[0] = GL_POINTS;
  if (ui_->line->isChecked()) settings_->begin_mode_2[1] = GL_LINE;
  if (ui_->triangle->isChecked()) settings_->begin_mode_2[2] = GL_TRIANGLES;
  if (!ui_->triangle->isChecked() && settings_->texture_loaded_) {
    settings_->texture_loaded_ = false;
    scene_->SendController().DeleteTexture();
  }
  scene_->update();
}

void Color::ResetSettings() {
  settings_->BaseSettings();
  LoadSettings();
  scene_->update();
}

void Color::LoadSettings() {
  LoadLineSettings();
  LoadVertexSettings();
  LoadOtherSettings();
}

void Color::LoadLineSettings() {
  if (settings_->line_mode_ == GL_LINE_STIPPLE) ui_->type_line_2->click();
  if (settings_->line_mode_ == GL_LINE) ui_->type_line_1->click();

  ui_->line_width->setValue(settings_->width_line_);

  ui_->color_line_r->setValue(settings_->color_line_.x());
  ui_->color_line_g->setValue(settings_->color_line_.y());
  ui_->color_line_b->setValue(settings_->color_line_.z());
}

void Color::LoadVertexSettings() {
  if (settings_->vertex_mode_ == GL_NONE) ui_->type_vert_nope->click();
  if (settings_->vertex_mode_ == GL_SQUARE) ui_->type_vert_sq->click();
  if (settings_->vertex_mode_ == GL_ROUND) ui_->type_vert_round->click();

  ui_->size_vertex->setValue(settings_->size_vertex_);

  ui_->color_ver_r->setValue(settings_->color_vertex_.x());
  ui_->color_ver_g->setValue(settings_->color_vertex_.y());
  ui_->color_ver_b->setValue(settings_->color_vertex_.z());
}

void Color::LoadOtherSettings() {
  ui_->color_back_r->setValue(settings_->color_back_.x());
  ui_->color_back_g->setValue(settings_->color_back_.y());
  ui_->color_back_b->setValue(settings_->color_back_.z());

  ui_->exterior_r->setValue(settings_->color_exterior_.x());
  ui_->exterior_g->setValue(settings_->color_exterior_.y());
  ui_->exterior_b->setValue(settings_->color_exterior_.z());

  if (settings_->begin_mode_2[0] == GL_POINTS) ui_->point->click();
  if (settings_->begin_mode_2[1] == GL_LINE) ui_->line->click();
  if (settings_->begin_mode_2[2] == GL_TRIANGLES) ui_->triangle->click();
}

}  // namespace s21
