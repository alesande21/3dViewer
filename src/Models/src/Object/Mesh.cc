#include "../../include/Object/Mesh.h"

namespace s21 {

void Mesh::Initialization(ObjectSettings *settings,
                          s21::ParseObject::data_type &object) {
  settings_ = settings;

  initializeOpenGLFunctions();
  va_.Generate();
  va_.Bind();

  vb_.SetData(object.value_of_vertexes_.size() * sizeof(s21::Ver3f),
              object.value_of_vertexes_.data(), GL_STATIC_DRAW);
  vb_.LinkVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);

  if (object.texture_vertex_.size() != 0) {
    settings_->has_uv_map_ = true;
    vb_.SetData(object.texture_vertex_.size() * sizeof(s21::Ver2f),
                object.texture_vertex_.data(), GL_STATIC_DRAW);
    vb_.LinkVertexAttribute(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                            (void *)0);
  } else {
    settings_->has_uv_map_ = false;
  }
  if (object.normal_vertex_.size() != 0) {
    vb_.SetData(object.own_normal_vertex_.size() * sizeof(s21::Ver3f),
                object.own_normal_vertex_.data(), GL_STATIC_DRAW);
    vb_.LinkVertexAttribute(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                            (void *)0);
  }
  eb_lines_.SetData(object.index_lines_.size() * sizeof(unsigned int),
                    object.index_lines_.data(), GL_STATIC_DRAW);
  eb_triangles_.SetData(object.index_triangles_.size() * sizeof(unsigned int),
                        object.index_triangles_.data(), GL_STATIC_DRAW);
  va_.Unbind();
  vb_.Unbind();
  eb_lines_.Unbind();
  eb_triangles_.Unbind();
}

void Mesh::CleanUp() {
  va_.Delete();
  vb_.Delete();
  eb_lines_.Delete();
  eb_triangles_.Delete();
}

void Mesh::Draw(Shader &shader_program, Camera &camera, Transformation &model) {
  shader_program.Activate();
  va_.Bind();

  int type_light_ambient =
      glGetUniformLocation(shader_program.GetShaderId(), "isDiffuse");
  glUniform1i(type_light_ambient, (settings_->type_light_ == AMBIENT));

  int type_light_specular =
      glGetUniformLocation(shader_program.GetShaderId(), "isPhong");
  glUniform1i(type_light_specular, (settings_->type_light_ == SPECULAR));

  int mode_light_carcass =
      glGetUniformLocation(shader_program.GetShaderId(), "isCarcass");
  glUniform1i(mode_light_carcass, (settings_->light_mode_ == CARCASS));

  int mode_light_flat =
      glGetUniformLocation(shader_program.GetShaderId(), "isFlatShade");
  glUniform1i(mode_light_flat, (settings_->light_mode_ == FLAT));

  int ambient_strenght =
      glGetUniformLocation(shader_program.GetShaderId(), "aAmbient");
  glUniform1f(ambient_strenght, settings_->ambient_strenght_);

  int specular_strenght =
      glGetUniformLocation(shader_program.GetShaderId(), "aSpecular");
  glUniform1f(specular_strenght, settings_->specular_strenght_);

  int cam_pos = glGetUniformLocation(shader_program.GetShaderId(), "camPos");
  glUniform3f(cam_pos, camera.GetPosition().x(), camera.GetPosition().y(),
              camera.GetPosition().z());

  camera.Matrix(shader_program, "camMatrix");
  model.Matrix(shader_program, "model");

  int light_color =
      glGetUniformLocation(shader_program.GetShaderId(), "lightColor");
  glUniform3f(light_color, settings_->light_color_.x() / 255.0f,
              settings_->light_color_.y() / 255.0f,
              settings_->light_color_.z() / 255.0f);
  int light_pos =
      glGetUniformLocation(shader_program.GetShaderId(), "lightPos");
  glUniform3f(light_pos, settings_->light_source_.x(),
              settings_->light_source_.y(), settings_->light_source_.z());
}

void Mesh::EboActivateLines() { eb_lines_.Bind(); }

void Mesh::EboDeactivateLines() { eb_lines_.Unbind(); }

void Mesh::EboDeactivateTriangles() { eb_triangles_.Unbind(); }

void Mesh::EboActivateTriangles() { eb_triangles_.Bind(); }

}  // namespace s21
