#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include "../../Models/include/Media/MediaSaver.h"

namespace s21 {
class MediaController {
 public:
  MediaController() = default;
  void SaveImage(const QString& filepath, QOpenGLWidget* glwidget);
  void SaveGif(const QString& filepath, QOpenGLWidget* glwidget);

 private:
  MediaSaver media_;
};
}  // namespace s21

#endif  // MEDIACONTROLLER_H
