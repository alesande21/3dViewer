#include "../include/MediaController.h"
namespace s21 {

void MediaController::SaveImage(const QString& filepath,
                                QOpenGLWidget* glwidget) {
  media_.SaveImage(filepath, glwidget);
}

void MediaController::SaveGif(const QString& filepath,
                              QOpenGLWidget* glwidget) {
  media_.SaveGif(filepath, glwidget);
}
}  // namespace s21
