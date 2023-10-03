#include "../../include/Texture/Texture.h"

namespace s21 {

void Texture::Initialize() { initializeOpenGLFunctions(); }

void Texture::Generate() { glGenTextures(1, &texture_); }

void Texture::Bind(GLenum target) { glBindTexture(target, texture_); }

void Texture::Unbind(GLenum target) { glBindTexture(target, 0); }

void Texture::Delete() { glDeleteTextures(1, &texture_); }

void Texture::SetTex(Shader &shader_id, const char *name) {
  GLuint tex0Uni = glGetUniformLocation(shader_id.GetShaderId(), name);
  shader_id.Activate();
  glUniform1i(tex0Uni, 0);
}

void Texture::LoadOrUnload(Shader &shader_id, ObjectSettings *settings) {
  shader_id.Activate();
  GLuint is_texture =
      glGetUniformLocation(shader_id.GetShaderId(), "isTexture");
  glUniform1i(is_texture, settings->texture_loaded_);
}

void Texture::SetData(GLenum target, GLenum texture, std::string filename) {
  if (filename.empty()) {
    qDebug() << "Ошибка! Нет пути к текстуре";
    return;
  }
  int num_col_ch{};

  bytes_ = SOIL_load_image(filename.c_str(), &width_img_, &height_img_,
                           &num_col_ch, SOIL_LOAD_AUTO);

  if (bytes_ == NULL) {
    qDebug() << "Текстура не загрузилась" << SOIL_last_result();
    return;
  }

  if (width_img_ > 1024 || height_img_ > 1024 || width_img_ != height_img_ ||
      width_img_ != height_img_) {
    qDebug()
        << "Texture resolution must not exceed 1024x1024 and must be square";
    SOIL_free_image_data(bytes_);
    return;
  }
  texture_ = SOIL_create_OGL_texture(
      bytes_, width_img_, height_img_, num_col_ch, texture_,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y);

  Unbind(target);
  SOIL_free_image_data(bytes_);
}

void Texture::SaveUVMap(const char *filename) {
  if (!filename) {
    qDebug() << "Нет пути для сохранения юв-карты";
    return;
  }
  QImage uvMap(width_img_, height_img_, QImage::Format_RGB888);
  for (int y = 0; y < height_img_; y++) {
    for (int x = 0; x < width_img_; x++) {
      int index = (y * width_img_ + x) * 3;
      QColor color(bytes_[index], bytes_[index + 1], bytes_[index + 2]);
      uvMap.setPixelColor(x, y, color);
    }
  }

  if (!uvMap.save(filename)) {
    qDebug() << "Ошибка при сохранении юв карты в bmp фаил.";
  }
}

}  // namespace s21
