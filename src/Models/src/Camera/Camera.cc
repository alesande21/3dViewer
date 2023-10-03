#include "../../include/Camera/Camera.h"

namespace s21 {

Camera &Camera::GetInstance() {
  static Camera instance;
  return instance;
}

void Camera::Initialization(int width, int height, QVector3D position,
                            ObjectSettings *settings) {
  QOpenGLFunctions glFunctions(QOpenGLContext::currentContext());
  initializeOpenGLFunctions();
  width_ = width;
  height_ = height;
  position_ = position;
  settings_ = settings;
}

void Camera::UpdateMatrix(float vertical_angle, float nearPlane,
                          float far_plane) {
  QMatrix4x4 view;
  QMatrix4x4 projection;
  if (settings_->type_camera_ == FOCUS) CalcFocusPos();
  if (settings_->type_camera_ == FOCUS)
    view.lookAt(position_, settings_->centre_object_, up_);
  if (settings_->type_camera_ == FREE)
    view.lookAt(position_, position_ + orientation_, up_);
  view.translate(translate_);
  GLfloat aspect_ratio = static_cast<float>(width_) / height_;
  float top = nearPlane;
  float bottom = -top;
  float left = bottom * aspect_ratio;
  float right = top * aspect_ratio;

  if (settings_->type_projections_ == PERSPECTIVE)
    projection.perspective(vertical_angle, static_cast<float>(width_) / height_,
                           nearPlane, far_plane);
  if (settings_->type_projections_ == PARALLEL)
    projection.ortho(left, right, bottom, top, nearPlane, far_plane);
  //    projection.ortho(left * scale_, right * scale_, bottom * scale_,
  //                     top * scale_, nearPlane, far_plane);
  camera_matrix_ = projection * view;
};

void Camera::Matrix(Shader &shader_program, const char *name) {
  int location_view = glGetUniformLocation(shader_program.GetShaderId(), name);
  glUniformMatrix4fv(location_view, 1, GL_FALSE, (camera_matrix_).constData());
};

bool Camera::Input(float delta) {
  if (delta > 0) scale_ = 1.1f;
  if (delta <= 0) scale_ = 0.9f;

  return true;
}

void Camera::Input(QVector2D dif) {
  if (settings_->type_camera_ == FREE) {
    dif = (-dif).normalized();
    float rotX = dif.x() * 5;
    float rotY = dif.y() * 5;
    QMatrix4x4 rotation_matrix;
    rotation_matrix.setToIdentity();
    QVector3D normal = (orientation_.crossProduct(orientation_, up_));
    normal.normalize();
    rotation_matrix.rotate(-rotX, normal);

    QVector3D new_orientation = rotation_matrix * orientation_;
    float dotProd = QVector3D::dotProduct(new_orientation, up_);
    float angle =
        qAcos(dotProd / (new_orientation.length() * up_.length())) * 180 / M_PI;
    if (abs(angle - 90.0f) <= 85.0f) {
      orientation_ = new_orientation;
    }

    rotation_matrix.setToIdentity();
    rotation_matrix.rotate(-rotY, up_);
    orientation_ = rotation_matrix.map(orientation_);
  }

  if (settings_->type_camera_ == FOCUS) {
    dif.normalize();
    sensitivity_ = 20 * M_PI / (std::min(width_, height_));
    float rot_x = dif.x() * sensitivity_;
    float rot_y = dif.y() * sensitivity_;
    focus_rotation_.setX(rot_x);
    focus_rotation_.setZ(rot_y);
  }
}

void Camera::CalcFocusPos() {
  constexpr double MIN_DIST = 0.01;
  float distance = (position_ - settings_->centre_object_).length();
  if (distance * scale_ > MIN_DIST) distance *= scale_;
  scale_ = 1;
  orientation_ = (position_ - settings_->centre_object_).normalized();
  if (orientation_.y() > 0.95) orientation_.setY(0.95);
  if (orientation_.y() < -0.95) orientation_.setY(-0.95);

  float pitch_angle = asin(orientation_.y());
  float yaw_angle = atan2(orientation_.x(), orientation_.z());

  pitch_angle -= focus_rotation_.z();
  yaw_angle -= focus_rotation_.x();
  focus_rotation_ = QVector3D();
  yaw_angle = fmod(yaw_angle, 2 * M_PI);

  QVector3D newDir(cos(pitch_angle) * sin(yaw_angle), sin(pitch_angle),
                   cos(pitch_angle) * cos(yaw_angle));
  position_ = settings_->centre_object_ + distance * newDir;
}

void Camera::Resize(int width, int height) {
  width_ = width;
  height_ = height;
}

void Camera::FreeMoveX(float sign) {
  if (settings_->type_camera_ == FOCUS) return;
  QVector3D distance;
  QVector3D rigth = QVector3D::normal(orientation_, up_);
  distance = rigth * sign * 0.1;
  distance *= speed_;
  position_ += distance;
}

void Camera::FreeMoveY(float sign) {
  if (settings_->type_camera_ == FOCUS) return;
  QVector3D distance;
  distance = orientation_ * sign;
  distance *= speed_;
  position_ += distance;
}

void Camera::FreeMoveZ(float sign) {
  if (settings_->type_camera_ == FOCUS) return;
  QVector3D distance;
  distance = up_ * sign;
  distance *= speed_;
  position_ += distance;
}

void Camera::MoreSpeed() { speed_ = 0.4f; }

void Camera::LessSpeed() { speed_ = 0.1f; }

QVector3D Camera::GetPosition() { return position_; }

}  // namespace s21
