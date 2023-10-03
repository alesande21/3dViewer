#ifndef MEDIASAVER_H
#define MEDIASAVER_H

#include <QImage>
#include <QObject>
#include <QOpenGLWidget>
#include <QTimer>

#include "../../../Views/include/Draw/DrawWidget.h"
#include "../../../include/QtGifImage/src/gifimage/qgifimage.h"

namespace s21 {

class MediaSaver : public QObject {
 public:
  void SaveImage(const QString& filepath, QOpenGLWidget* glwidget);
  void SaveGif(const QString& filepath, QOpenGLWidget* glwidget);

 private:
  QImage TakeSnapshot(QOpenGLWidget* glwidget,
                      std::optional<int> w = std::nullopt,
                      std::optional<int> h = std::nullopt);
  QGifImage* gif_;
  QTimer* timer_;
  int time_ = 0;
  bool timer_ready_ = true;

 private slots:
  void TakeGif(const QString& filepath, QOpenGLWidget* glwidget);
};
}  // namespace s21

#endif  // MEDIASAVER_H
