#include "../../include/Object/Object.h"

namespace s21 {

void Object::SetSettings(ObjectSettings *settings) {
  initializeOpenGLFunctions();
  settings_ = settings;
}

void Object::UploadObjectFromFile(s21::ParseObject::data_type object) {
  QFile::remove("temp_trans_settings.ini");
  QFile::remove("temp_camera_settings.ini");
  object_ = object;
  settings_->centre_object_ = ObjectCentre();
  LoadMesh();
}

void Object::LoadMesh() {
  if (!object_.texture_vertex_.empty()) settings_->has_uv_map_ = true;
  mesh_.Initialization(settings_, object_);
}

void Object::DrawObject(Shader &shader_program) {
  GLint color = glGetUniformLocation(shader_program.GetShaderId(), "Color2");
  if (settings_->begin_mode_2[2] == GL_TRIANGLES) {
    mesh_.EboActivateTriangles();
    glUniform3f(color, settings_->color_exterior_.x() / 255,
                settings_->color_exterior_.y() / 255,
                settings_->color_exterior_.z() / 255);
    glDrawElements(GL_TRIANGLES, object_.index_triangles_.size(),
                   GL_UNSIGNED_INT, 0);
    mesh_.EboDeactivateTriangles();
  }
  if (settings_->begin_mode_2[1] == GL_LINE) {
    mesh_.EboActivateLines();
    if (settings_->line_mode_ == GL_LINE_STIPPLE) TypeLine(shader_program);
    glUniform3f(color, settings_->color_line_.x() / 255,
                settings_->color_line_.y() / 255,
                settings_->color_line_.z() / 255);
    glDrawElements(GL_LINES, object_.index_lines_.size(), GL_UNSIGNED_INT, 0);
    mesh_.EboDeactivateLines();
  }
  if (settings_->vertex_mode_ != 0 && settings_->begin_mode_2[0] == GL_POINTS) {
    mesh_.EboActivateLines();
    glEnable(GL_PROGRAM_POINT_SIZE);
    int point_size =
        glGetUniformLocation(shader_program.GetShaderId(), "vertexSize");
    glUniform1f(point_size, settings_->size_vertex_);
    glUniform3f(color, settings_->color_vertex_.x() / 255,
                settings_->color_vertex_.y() / 255,
                settings_->color_vertex_.z() / 255);
    int bool_point =
        glGetUniformLocation(shader_program.GetShaderId(), "isRoundPoint");
    if (settings_->vertex_mode_ == 2) glUniform1i(bool_point, true);
    glDrawElements(GL_POINTS, object_.index_triangles_.size(), GL_UNSIGNED_INT,
                   0);
    if (settings_->vertex_mode_ == 2) glUniform1i(bool_point, false);
    if (settings_->line_mode_ == GL_LINE_STIPPLE) OffStripple(shader_program);
    glDisable(GL_PROGRAM_POINT_SIZE);
    mesh_.EboDeactivateLines();
  }
}

void Object::Draw(Shader &shader_program, Camera &camera, Transformation &model,
                  Texture &texture) {
  if (object_.value_of_vertexes_.empty()) return;
  mesh_.Draw(shader_program, camera, model);
  texture.Bind(GL_TEXTURE_2D);
  DrawObject(shader_program);
}

void Object::CleanUp() { mesh_.CleanUp(); }

void Object::TypeLine(Shader &shader_program) {
  GLint is_stripple =
      glGetUniformLocation(shader_program.GetShaderId(), "isStripple");
  glUniform1i(is_stripple, true);
  GLint loc_resolution =
      glGetUniformLocation(shader_program.GetShaderId(), "u_resolution");
  GLint loc_dashSize =
      glGetUniformLocation(shader_program.GetShaderId(), "u_dashSize");
  GLint loc_gapSize =
      glGetUniformLocation(shader_program.GetShaderId(), "u_gapSize");

  glUniform2f(loc_resolution, 1500.0, 1000.0);
  glUniform1f(loc_dashSize, 10.0);
  glUniform1f(loc_gapSize, 10.0);
}

void Object::OffStripple(Shader &shader_program) {
  GLint is_stripple =
      glGetUniformLocation(shader_program.GetShaderId(), "isStripple");
  glUniform1i(is_stripple, false);
}

QVector3D Object::ObjectCentre() {
  GLfloat center_x = 0.0f;
  GLfloat center_y = 0.0f;
  GLfloat center_z = 0.0f;

  auto it = object_.value_of_vertexes_.begin();

  for (; it != object_.value_of_vertexes_.end(); it++) {
    center_x += it->x;
    center_y += it->y;
    center_z += it->z;
  }

  center_x /= object_.value_of_vertexes_.size();
  center_y /= object_.value_of_vertexes_.size();
  center_z /= object_.value_of_vertexes_.size();

  QVector3D object_center(center_x, center_y, center_z);
  return object_center;
}

s21::ParseObject::data_type &Object::SendObject() { return object_; }

}  // namespace s21
