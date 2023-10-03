#ifndef OBJECTSETTINGS_H
#define OBJECTSETTINGS_H

#include <QDebug>
#include <QFileDialog>
#include <QOpenGLFunctions>
#include <QSettings>
#include <QVector3D>
#include <cassert>

// type vertex
#define GL_NONE 0
#define GL_SQUARE 1
#define GL_ROUND 2

// camera type
#define FREE 3
#define FOCUS 4

// type projection
#define PERSPECTIVE 5
#define PARALLEL 6

// light mode
#define CARCASS 7
#define FLAT 8
#define SMOOTH 9

// type light
#define AMBIENT 10
#define SPECULAR 11

//#define CHECK_GL_ERROR() CheckGLError(__FILE__, __LINE__)

// void CheckGLError(const char* file, int line) {
//     GLenum error = glGetError();
//     if (error != GL_NO_ERROR) {
//         const char* errorString = reinterpret_cast<const
//         char*>(glewGetErrorString(error)); qDebug() << "OpenGL error (" <<
//         errorString << ") at " << file << ":" << line;
//         // Здесь можно добавить дополнительную информацию о месте и файле.
//         // Например, можно использовать макросы __FUNCTION__ или
//         __PRETTY_FUNCTION__
//         // для вывода имени текущей функции.
//         assert(false); // Прерываем выполнение программы при обнаружении
//         ошибки.
//     }
// }

namespace s21 {

struct ObjectSettings {
  // настройки цвета, линий и вершин (Class Color)
  QVector3D color_exterior_ = {255.0f, 255.0f, 255.0f};
  QVector3D color_back_ = {0.0f, 0.0f, 0.0f};
  QVector3D color_vertex_ = {255.0f, 0.0f, 0.0f};
  QVector3D color_line_ = {0.0f, 255.0f, 0.0f};
  GLenum line_mode_ = GL_LINE_STIPPLE;
  GLint vertex_mode_ = 0;
  GLint size_vertex_ = 0;
  GLint width_line_ = 0;
  // настройка камеры
  GLint type_camera_ = FOCUS;
  GLint type_projections_ = PERSPECTIVE;
  GLenum begin_mode_2[3] = {GL_POINTS, GL_LINE, GL_TRIANGLES};
  QVector3D centre_object_ = {0, 0, 0};
  GLfloat near_plane_ = 0.1;
  GLfloat far_plane_ = 1000000;
  GLfloat fov_ = 45;
  //настройка света
  GLint light_mode_ = 7;
  GLint type_light_ = 10;
  QVector3D light_source_ = {3.2f, 0.5f, 0.5f};
  QVector3D light_color_ = {255.0f, 255.0f, 255.0f};
  GLfloat ambient_strenght_ = 0.1f;
  GLfloat specular_strenght_ = 0.5f;
  //настройка текстуры
  GLboolean has_uv_map_ = false;
  GLboolean texture_loaded_ = false;

  ObjectSettings() { LoadSettings(); }

  void LoadSettings() {
    QSettings qsettings_("settings.ini", QSettings::IniFormat);
    color_exterior_ =
        qsettings_.value("color_exterior_", QVector3D(255.0f, 104.0f, 0.0f))
            .value<QVector3D>();
    color_back_ =
        qsettings_.value("color_back_", QVector3D(61.0f, 61.0f, 61.0f))
            .value<QVector3D>();
    color_vertex_ =
        qsettings_.value("color_vertex_", QVector3D(255.0f, 104.0f, 0.0f))
            .value<QVector3D>();
    color_line_ =
        qsettings_.value("color_line_", QVector3D(255.0f, 104.0f, 0.0f))
            .value<QVector3D>();
    line_mode_ = qsettings_.value("line_mode_", GL_LINE).value<GLenum>();
    vertex_mode_ = qsettings_.value("vertex_mode_", GL_ROUND).value<GLint>();
    width_line_ = qsettings_.value("width_line_", 0).value<GLint>();
    type_projections_ =
        qsettings_.value("type_projections_", PERSPECTIVE).value<GLint>();
    vertex_mode_ = qsettings_.value("vertex_mode_", GL_ROUND).value<GLint>();
    ReloadOtherSettings();
  }

  void ReloadOtherSettings() {
    light_mode_ = 7;
    type_light_ = 10;
    light_source_ = {3.2f, 0.5f, 0.5f};
    light_color_ = {255.0f, 255.0f, 255.0f};
    ambient_strenght_ = 0.1f;
    specular_strenght_ = 0.5f;
    texture_loaded_ = false;
  }

  void SaveSettings() {
    QSettings qsettings_("settings.ini", QSettings::IniFormat);
    qsettings_.setValue("color_exterior_", color_exterior_);
    qsettings_.setValue("color_back_", color_back_);
    qsettings_.setValue("color_vertex_", color_vertex_);
    qsettings_.setValue("color_line_", color_line_);
    qsettings_.setValue("line_mode_", line_mode_);
    qsettings_.setValue("vertex_mode_", vertex_mode_);
    qsettings_.setValue("size_vertex_", size_vertex_);
    qsettings_.setValue("width_line_", width_line_);
    qsettings_.setValue("type_projections_", type_projections_);
  }

  void BaseSettings() {
    QFile::remove("settings.ini");
    LoadSettings();
  }
};
}  // namespace s21

#endif  // OBJECTSETTINGS_H
