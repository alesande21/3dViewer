#include "../include/CameraController.h"

namespace s21 {

CameraController::CameraController() { camera_ = &Camera::GetInstance(); }

void CameraController::LoadCameraSettings(int width, int height,
                                          QVector3D position,
                                          ObjectSettings *settings) {
  camera_->Initialization(width, height, position, settings);
}

void CameraController::UpdateCamera(float vertical_angle, float nearPlane,
                                    float far_plane) {
  camera_->UpdateMatrix(vertical_angle, nearPlane, far_plane);
}

bool CameraController::UpdateScale(int y) { return camera_->Input(-1 * y); }

void CameraController::UpdateMoving(QPoint pos_new, QPoint pos_old) {
  camera_->Input(QVector2D(pos_new - pos_old));
}

void CameraController::Resize(int width, int height) {
  camera_->Resize(width, height);
}

void CameraController::Zoom(float prev, float curr) {
  camera_->Input(curr - prev);
}

void CameraController::FreeMoveX(float prev, float curr) {
  camera_->FreeMoveX((curr - prev) > 0 ? 1 : -1);
}

void CameraController::FreeMoveY(float prev, float curr) {
  camera_->FreeMoveY((curr - prev) > 0 ? 1 : -1);
}

void CameraController::FreeMoveZ(float prev, float curr) {
  camera_->FreeMoveZ((curr - prev) > 0 ? 1 : -1);
}

void CameraController::MoreSpeed() { camera_->MoreSpeed(); }

void CameraController::LessSpeed() { camera_->LessSpeed(); }

Camera &CameraController::GetCamera() { return *camera_; }

}  // namespace s21
