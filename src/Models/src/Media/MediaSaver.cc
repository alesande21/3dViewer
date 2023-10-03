
#include "../../include/Media/MediaSaver.h"
namespace s21 {
void MediaSaver::SaveImage(const QString& filepath, QOpenGLWidget* glwidget) {
  if (!filepath.isEmpty()) {
    QImage snapshot = TakeSnapshot(glwidget);
    snapshot.save(filepath, NULL, 100);
  }
}

void MediaSaver::SaveGif(const QString& filepath, QOpenGLWidget* glwidget) {
  if (!filepath.isEmpty()) {
    if (timer_ready_) {
      gif_ = new QGifImage();
      timer_ = new QTimer();
    }

    timer_->start(100);
    connect(timer_, &QTimer::timeout, this,
            [this, filepath, glwidget]() { TakeGif(filepath, glwidget); });

    timer_ready_ = false;
  }
}

void MediaSaver::TakeGif(const QString& filepath, QOpenGLWidget* glwidget) {
  time_++;
  QImage image = TakeSnapshot(glwidget, 640, 480);

  gif_->setDefaultDelay(10);
  gif_->addFrame(image);

  if (time_ == 50) {
    time_ = 0;
    timer_->stop();
    gif_->save(filepath);
    image.QImage::bits();
    timer_ready_ = true;
    delete timer_;
    delete gif_;
  }
}

QImage MediaSaver::TakeSnapshot(QOpenGLWidget* glwidget, std::optional<int> w,
                                std::optional<int> h) {
  QImage snapshot;
  if (w.has_value() && h.has_value()) {
    snapshot = glwidget->grabFramebuffer().scaled(w.value(), h.value());
  } else {
    snapshot = glwidget->grabFramebuffer();
  }
  return snapshot;
}
}  // namespace s21
