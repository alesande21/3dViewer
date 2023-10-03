#include "../../include/Shader/Shader.h"

namespace s21 {

bool Shader::CompileSuccessful(int obj) {
  int status;
  glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
  return status == GL_TRUE;
}
void Shader::PrintShaderError(int obj) {
  GLint maxLength = 0;
  glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
  std::vector<GLchar> errorLog(maxLength);
  glGetShaderInfoLog(obj, maxLength, &maxLength, &errorLog[0]);
  qDebug() << errorLog.data();
}

std::string Shader::GetFileContents(const char* filename) {
  QFile file(QString::fromUtf8(filename));

  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream stream(&file);
    QString contents = stream.readAll();
    file.close();
    return contents.toStdString();
  } else {
    qDebug() << "Файл не открылся!";
    return "";
  }
}

void Shader::SetData(const char* vertex_file, const char* fragment_file) {
  QOpenGLExtraFunctions glFunctions(QOpenGLContext::currentContext());
  initializeOpenGLFunctions();

  if (vertex_file == nullptr || fragment_file == nullptr) {
    qDebug() << "Нет путей файлов к шейдерам!";
    return;
  }

  id_ = glCreateProgram();

  std::string vertex_code = GetFileContents(vertex_file);
  std::string fragment_code = GetFileContents(fragment_file);

  const char* vertex_shader_source = vertex_code.c_str();
  const char* fragment_shader_source = fragment_code.c_str();

  GLuint vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertex_shader_, 1, &vertex_shader_source, NULL);

  glCompileShader(vertex_shader_);
  if (!CompileSuccessful(vertex_shader_)) PrintShaderError(vertex_shader_);
  glShaderSource(fragment_shader_, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader_);
  if (!CompileSuccessful(fragment_shader_)) PrintShaderError(fragment_shader_);
  glAttachShader(id_, vertex_shader_);
  glAttachShader(id_, fragment_shader_);
  glLinkProgram(id_);
  if (!CompileSuccessful(id_)) PrintShaderError(id_);
  glDeleteShader(vertex_shader_);
  glDeleteShader(fragment_shader_);
}

void Shader::SetAll(const char* vertex_file, const char* fragment_file,
                    const char* geom_file) {
  QOpenGLExtraFunctions glFunctions(QOpenGLContext::currentContext());
  initializeOpenGLFunctions();

  id_ = glCreateProgram();

  std::string vertex_code = GetFileContents(vertex_file);
  std::string fragment_code = GetFileContents(fragment_file);
  std::string geom_code = GetFileContents(geom_file);

  const char* vertex_shader_source = vertex_code.c_str();
  const char* fragment_shader_source = fragment_code.c_str();
  const char* geom_shader_source = geom_code.c_str();

  GLuint vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint geom_shader_ = glCreateShader(GL_GEOMETRY_SHADER_EXT);

  glShaderSource(geom_shader_, 1, &geom_shader_source, NULL);
  glCompileShader(geom_shader_);
  if (!CompileSuccessful(geom_shader_)) PrintShaderError(geom_shader_);

  glShaderSource(vertex_shader_, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader_);
  if (!CompileSuccessful(vertex_shader_)) PrintShaderError(vertex_shader_);
  glShaderSource(fragment_shader_, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader_);
  if (!CompileSuccessful(fragment_shader_)) PrintShaderError(fragment_shader_);
  glAttachShader(id_, vertex_shader_);
  glAttachShader(id_, geom_shader_);
  glAttachShader(id_, fragment_shader_);
  glLinkProgram(id_);
  if (!CompileSuccessful(id_)) PrintShaderError(id_);
  glDeleteShader(vertex_shader_);
  glDeleteShader(fragment_shader_);
  glDeleteShader(geom_shader_);
}

void Shader::Activate() { glUseProgram(id_); }

void Shader::Delete() { glDeleteProgram(id_); }

GLuint Shader::GetShaderId() { return id_; }

}  // namespace s21
