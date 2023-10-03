#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QApplication>
#include <QCursor>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QGuiApplication>
#include <QMessageBox>
#include <QMouseEvent>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QScreen>
#include <QSettings>
#include <QTimer>
#include <QtGui/QWheelEvent>
#include <filesystem>

#include "../../../Controlers/include/CameraController.h"
#include "../../../Controlers/include/ObjectController.h"
#include "../../../Settings/ObjectSettings.h"
#include "../../../include/stb/stb_image.h"

namespace s21 {
class DrawWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  DrawWidget(QWidget *parent = nullptr);
  ~DrawWidget();
  void SetSettings(ObjectSettings &settings);
  ObjectController &SendController();
  CameraController &SendCameraController();

 private:
  ObjectController object_controller_;
  CameraController camera_controller_;
  ObjectSettings *settings_;
  bool left_btn_ = false;
  QPoint mPos_;

 private slots:
  void resizeEvent(QResizeEvent *event) override;
  void mousePressEvent(QMouseEvent *mo) override;
  void mouseMoveEvent(QMouseEvent *mo) override;
  void mouseReleaseEvent(QMouseEvent *mo) override;
  void wheelEvent(QWheelEvent *mo) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void keyPressEvent(QKeyEvent *event) override;
  void ObjectTransformation(QKeyEvent *event);
  void CameraTransformation(QKeyEvent *event);
};
}  // namespace s21
#endif  // DRAWWIDGET_H
