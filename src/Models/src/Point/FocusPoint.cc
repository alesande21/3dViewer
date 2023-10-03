#include "../../include/Point/FocusPoint.h"

namespace s21 {

void FocusPoint::SetSettings(ObjectSettings *settings) {
  initializeOpenGLFunctions();
  settings_ = settings;
  LoadShader();
  tr_.Initialization();
}

void FocusPoint::LoadShader() {
  QString current_path = QDir::currentPath();
#ifdef _WIN32
  shader_program_point_.SetData(
      QString(":/Shaders/light.vert").toUtf8().constData(),
      QString(":/Shaders/light.frag").toUtf8().constData());
#elif __APPLE__
  shader_program_point_.SetData(
      QString(":/Shaders/light.vert").toUtf8().constData(),
      QString(":/Shaders/light.frag").toUtf8().constData());

#endif
}

void FocusPoint::LoadPoint(std::vector<GLfloat> vertex,
                           std::vector<GLuint> index) {
  va_.Generate();
  va_.Bind();
  vb_.SetData(sizeof(GLfloat) * vertex.size(), vertex.data(), GL_STATIC_DRAW);
  vb_.LinkVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
  eb_.SetData(sizeof(GLuint) * index.size(), index.data(), GL_STATIC_DRAW);
  va_.Unbind();
  vb_.Unbind();
  eb_.Unbind();
}

void FocusPoint::UpdatePoint(Camera &camera, std::vector<GLuint> index,
                             QVector3D color_vertex, GLint size_point) {
  shader_program_point_.Activate();
  camera.Matrix(shader_program_point_, "camMatrix");
  tr_.Matrix(shader_program_point_, "model");
  va_.Bind();
  eb_.Bind();
  GLint color =
      glGetUniformLocation(shader_program_point_.GetShaderId(), "Color2");
  glEnable(GL_PROGRAM_POINT_SIZE);
  int point_size =
      glGetUniformLocation(shader_program_point_.GetShaderId(), "vertexSize");
  glUniform1f(point_size, size_point);
  glGetError();
  glUniform3f(color, color_vertex.x() / 255, color_vertex.y() / 255,
              color_vertex.z() / 255);
  int bool_point =
      glGetUniformLocation(shader_program_point_.GetShaderId(), "isRoundPoint");
  glUniform1i(bool_point, true);
  glDrawElements(GL_POINTS, index.size(), GL_UNSIGNED_INT, 0);
  glUniform1i(bool_point, false);
  glDisable(GL_PROGRAM_POINT_SIZE);
  eb_.Unbind();
}

void FocusPoint::UpdateTransform(QVector3D new_pos) {
  static QVector3D old_pos = {0.5, 0.5, 0.5};
  if (old_pos != new_pos) {
    QVector3D change_pos = new_pos - old_pos;
    tr_.Translate(change_pos.x(), change_pos.y(), change_pos.z());
  }
  old_pos = new_pos;
}

}  // namespace s21

//#define GL_INVALID_VALUE                  0x0501
