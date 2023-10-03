#include "../../include/Draw/DrawWidget.h"

namespace s21 {

DrawWidget::DrawWidget(QWidget *parent) : QOpenGLWidget(parent) {
  setGeometry(1000, 1000, 1000, 1000);
  this->setFocus();
}

void DrawWidget::initializeGL() {
  QOpenGLFunctions glFunctions(QOpenGLContext::currentContext());
  qDebug() << "OpenGL version:"
           << reinterpret_cast<const char *>(
                  glFunctions.glGetString(GL_VERSION));
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  object_controller_.Initialize(settings_);
  object_controller_.LoadShader();
  object_controller_.InitializeTexture();
  camera_controller_.LoadCameraSettings(this->size().width(),
                                        this->size().height(),
                                        {0.0f, 0.0f, 10.0f}, settings_);
  object_controller_.LoadPoint(settings_);
}

void DrawWidget::resizeGL(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  camera_controller_.Resize(this->size().width(), this->size().height());
}

void DrawWidget::paintGL() {
  glClearColor(settings_->color_back_.x() / 255.0f,
               settings_->color_back_.y() / 255.0f,
               settings_->color_back_.z() / 255.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  camera_controller_.UpdateCamera(settings_->fov_, settings_->near_plane_,
                                  settings_->far_plane_);
  object_controller_.DrawObject(camera_controller_.GetCamera());
  object_controller_.DrawPoint(settings_, camera_controller_.GetCamera());
}

void DrawWidget::SetSettings(ObjectSettings &settings) {
  settings_ = &settings;
}

DrawWidget::~DrawWidget() {}

ObjectController &DrawWidget::SendController() { return object_controller_; }

CameraController &DrawWidget::SendCameraController() {
  return camera_controller_;
}

void DrawWidget::keyPressEvent(QKeyEvent *event) {
  CameraTransformation(event);
  ObjectTransformation(event);
  update();
}

void DrawWidget::ObjectTransformation(QKeyEvent *event) {
  if (event->key() == Qt::Key_I) {
    object_controller_.TranslateY(0.0f, 1.0f);
  } else if (event->key() == Qt::Key_K) {
    object_controller_.TranslateY(1.0f, 0.0f);
  } else if (event->key() == Qt::Key_J) {
    object_controller_.TranslateX(1.0f, 0.0f);
  } else if (event->key() == Qt::Key_L) {
    object_controller_.TranslateX(0.0f, 1.0f);
  } else if (event->key() == Qt::Key_9) {
    object_controller_.Scale(1.0f, 0.0f);
  } else if (event->key() == Qt::Key_3) {
    object_controller_.Scale(0.0f, 1.0f);
  } else if (event->key() == Qt::Key_4) {
    object_controller_.RotationY(1.0f, 0.0f);
  } else if (event->key() == Qt::Key_6) {
    object_controller_.RotationY(0.0f, 1.0f);
  } else if (event->key() == Qt::Key_8) {
    object_controller_.RotationX(1.0f, 0.0f);
  } else if (event->key() == Qt::Key_2) {
    object_controller_.RotationX(0.0f, 1.0f);
  } else if (event->key() == Qt::Key_7) {
    object_controller_.RotationZ(1.0f, 0.0f);
  } else if (event->key() == Qt::Key_1) {
    object_controller_.RotationZ(0.0f, 1.0f);
  }
}

void DrawWidget::CameraTransformation(QKeyEvent *event) {
  if (event->key() == Qt::Key_W) {
    camera_controller_.FreeMoveY(1.0f, 0.0f);
  } else if (event->key() == Qt::Key_A) {
    camera_controller_.FreeMoveX(0.0f, 1.0f);
  } else if (event->key() == Qt::Key_S) {
    camera_controller_.FreeMoveY(0.0f, 1.0f);
  } else if (event->key() == Qt::Key_D) {
    camera_controller_.FreeMoveX(1.0f, 0.0f);
  } else if (event->key() == Qt::Key_X) {
    camera_controller_.FreeMoveZ(1.0f, 0.0f);
  } else if (event->key() == Qt::Key_Z) {
    camera_controller_.FreeMoveZ(0.0f, 1.0f);
  } else if (event->key() == Qt::Key_C) {
    camera_controller_.LessSpeed();
  } else if (event->key() == Qt::Key_V) {
    camera_controller_.MoreSpeed();
  }
}

void DrawWidget::wheelEvent(QWheelEvent *mo) {
  if (camera_controller_.UpdateScale(mo->angleDelta().ry())) update();
}

void DrawWidget::mousePressEvent(QMouseEvent *mo) {
  if (mo->button() == Qt::LeftButton) {
    left_btn_ = true;
    mPos_ = mo->pos();
  }
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *mo) {
  Q_UNUSED(mo);
  if (left_btn_) left_btn_ = false;
}

void DrawWidget::mouseMoveEvent(QMouseEvent *mo) {
  if (left_btn_) {
    camera_controller_.UpdateMoving(mo->pos(), mPos_);
    mPos_ = mo->pos();
    update();
  }
}

void DrawWidget::resizeEvent(QResizeEvent *event) {
  int width = event->size().width();
  int height = event->size().height();
  camera_controller_.Resize(width, height);
  update();
  QWidget::resizeEvent(event);
}

}  // namespace s21
