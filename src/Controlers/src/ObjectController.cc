#include "../include/ObjectController.h"

namespace s21 {

ObjectController::~ObjectController() {
  texture_.Delete();
  shader_program_.Delete();
}

void ObjectController::Initialize(ObjectSettings *settings) {
  initializeOpenGLFunctions();
  transformation_.Initialization();
  settings_ = settings;
  object_.SetSettings(settings_);
  current_path_ = QDir::currentPath();
}

void ObjectController::LoadPoint(ObjectSettings *settings) {
  point_centre_.SetSettings(settings);
  point_light_.SetSettings(settings);
  point_centre_.LoadPoint({0, 0, 0}, {0});
  point_light_.LoadPoint({0.5, 0.5, 0.5}, {0});
}

void ObjectController::DrawPoint(ObjectSettings *settings, Camera &camera) {
  //    point_.UpdateTransform(settings->centre_object_);
  point_centre_.LoadPoint(
      {settings->centre_object_.x(), settings->centre_object_.y(),
       settings->centre_object_.z()},
      {0});
  point_centre_.UpdatePoint(camera, {0}, {255, 0, 0}, 20);
  point_light_.UpdateTransform(settings->light_source_);
  if (settings->light_mode_ != 7) {
    point_light_.UpdatePoint(camera, {0}, settings->light_color_, 30);
  }
}

void ObjectController::LoadShader() {
#ifdef _WIN32
  shader_program_.SetData(
      QString(":/Shaders/default.vert").toUtf8().constData(),
      QString(":/Shaders/default.frag").toUtf8().constData());
#elif __APPLE__
  shader_program_.SetData(
      QString(":/Shaders/default.vert").toUtf8().constData(),
      QString(":/Shaders/default.frag").toUtf8().constData());

#endif
}

void ObjectController::InitializeTexture() { texture_.Initialize(); }

void ObjectController::UpdateTexture(QString path_to_texture) {
#ifdef _WIN32
  texture_.SetData(GL_TEXTURE_2D, GL_TEXTURE0,
                   (path_to_texture).toUtf8().constData());
#elif __APPLE__
  texture_.SetData(GL_TEXTURE_2D, GL_TEXTURE0, (path_to_texture).toStdString());
#endif
  texture_.SetTex(shader_program_, "tex0");
  texture_.LoadOrUnload(shader_program_, settings_);
}

void ObjectController::DeleteTexture() {
  texture_.LoadOrUnload(shader_program_, settings_);
  texture_.Delete();
}

void ObjectController::DrawObject(Camera &camera) {
  object_.Draw(shader_program_, camera, transformation_, texture_);
}

void ObjectController::RotationX(float prev, float curr) {
  transformation_.Rotation(1.0, (curr - prev) > 0 ? 1 : -1, 0.0f, 0.0f);
}

void ObjectController::RotationY(float prev, float curr) {
  transformation_.Rotation(1.0, 0.0f, (curr - prev) > 0 ? 1 : -1, 0.0f);
}

void ObjectController::RotationZ(float prev, float curr) {
  transformation_.Rotation(1.0, 0.0f, 0.0f, (curr - prev) > 0 ? 1 : -1);
}

void ObjectController::TranslateX(float prev, float curr) {
  transformation_.Translate((curr - prev) > 0 ? 0.1 : -0.1, 0.0f, 0.0f);
}

void ObjectController::TranslateY(float prev, float curr) {
  transformation_.Translate(0.0f, (curr - prev) > 0 ? 0.1 : -0.1, 0.0f);
}

void ObjectController::TranslateZ(float prev, float curr) {
  transformation_.Translate(0.0f, 0.0f, (curr - prev) > 0 ? 0.1 : -0.1);
}
void ObjectController::Scale(float prev, float curr) {
  transformation_.Scale((curr - prev) > 0 ? 1.1 : 1.0 / 1.1,
                        (curr - prev) > 0 ? 1.1 : 1.0 / 1.1,
                        (curr - prev) > 0 ? 1.1 : 1.0 / 1.1);
}

void ObjectController::CleanUp() { object_.CleanUp(); }

void ObjectController::SaveUvMap(const char *filename) {
  texture_.SaveUVMap(filename);
}

void ObjectController::UploadObjectFromFile(const std::string &filepath) {
  texture_.Delete();
  object_.UploadObjectFromFile(parser_.Parser(filepath));
}

s21::ParseObject::data_type ObjectController::GetObject() {
  return object_.SendObject();
}

}  // namespace s21
