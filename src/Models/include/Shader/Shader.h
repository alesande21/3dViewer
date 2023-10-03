#ifndef SHADER_H
#define SHADER_H

#include <QFile>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace s21 {
class Shader : public QOpenGLExtraFunctions {
 public:
  Shader() = default;
  Shader(const char* vertex_file, const char* fragment_file);
  void SetData(const char* vertex_file, const char* fragment_file);
  void SetAll(const char* vertex_file, const char* fragment_file,
              const char* geom_file);
  void Activate();
  void Delete();
  GLuint GetShaderId();

 private:
  GLuint id_;

 private slots:
  std::string GetFileContents(const char* filename);
  bool CompileSuccessful(int obj);
  void PrintShaderError(int obj);
};
}  // namespace s21

#endif  // SHADER_H
