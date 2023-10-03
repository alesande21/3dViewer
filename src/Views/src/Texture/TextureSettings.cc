#include "../../include/Texture/TextureSettings.h"

#include "ui_texturesettings.h"

namespace s21 {

TextureSettings::TextureSettings(ObjectSettings &settings, DrawWidget &opengl,
                                 QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::TextureSettings),
      opengl_(&opengl),
      settings_(&settings) {
  ui_->setupUi(this);

  LoadStatusUv();
  if (settings_->has_uv_map_) {
    connect(ui_->loadTexture, QOverload<bool>::of(&QPushButton::clicked), this,
            &TextureSettings::LoadTexture);
    connect(ui_->unloadTexture, QOverload<bool>::of(&QPushButton::clicked),
            this, &TextureSettings::UnloadTexture);
    connect(ui_->saveUVmap, QOverload<bool>::of(&QPushButton::clicked), this,
            &TextureSettings::SaveUvMap);
  }
}

TextureSettings::~TextureSettings() { delete ui_; }

void TextureSettings::LoadTexture() {
  if (!settings_->has_uv_map_) return;
  settings_->texture_loaded_ = true;
  settings_->begin_mode_2[0] = 0;
  settings_->begin_mode_2[1] = 0;
  settings_->begin_mode_2[2] = GL_TRIANGLES;
  QString file =
      QFileDialog::getOpenFileName(this, "Upload Texture ", "", "BMP (*.BMP)");
  opengl_->SendController().UpdateTexture(file);
  opengl_->update();
}

void TextureSettings::UnloadTexture() {
  if (!settings_->has_uv_map_) return;
  settings_->texture_loaded_ = false;
  opengl_->SendController().DeleteTexture();
  opengl_->update();
}

void TextureSettings::LoadStatusUv() {
  if (settings_->has_uv_map_) {
    ui_->status_uv_map->setText("Uv карта объекта доступна");
    ui_->status_uv_map->setStyleSheet("border: 2px solid #006400;");
    ui_->loadTexture->setStyleSheet("border: 2px solid rgba(204, 0, 204, 0.6)");
    ui_->saveUVmap->setStyleSheet("border: 2px solid rgba(204, 0, 204, 0.6)");
    ui_->unloadTexture->setStyleSheet(
        "border: 2px solid rgba(204, 0, 204, 0.6)");
  } else {
    ui_->loadTexture->setStyleSheet("border: 1px solid rgba(204, 0, 204, 0.3)");
    ui_->unloadTexture->setStyleSheet(
        "border: 1px solid rgba(204, 0, 204, 0.3)");
    ui_->saveUVmap->setStyleSheet("border: 1px solid rgba(204, 0, 204, 0.3)");
    ui_->status_uv_map->setText("Uv карта объекта недоступна");
    ui_->status_uv_map->setStyleSheet("border: 2px solid rgba(255, 0, 0, 0.6)");
  }
}

void TextureSettings::SaveUvMap() {
  if (!settings_->has_uv_map_) return;
  QString filepath = QFileDialog::getSaveFileName(
      this, "Save as...", "saveUvMap.bmp", "Images (*.bmp)");
  if (!filepath.isEmpty()) {
    opengl_->SendController().SaveUvMap(filepath.toStdString().c_str());
  }
}

}  // namespace s21
