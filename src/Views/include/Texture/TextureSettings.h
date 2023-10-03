#ifndef TEXTURESETTINGS_H
#define TEXTURESETTINGS_H

#include <QOpenGLFunctions>
#include <QWidget>

#include "../../../Settings/ObjectSettings.h"
#include "../Draw/DrawWidget.h"

namespace Ui {
class TextureSettings;
}
namespace s21 {
class TextureSettings : public QWidget {
  Q_OBJECT

 public:
  explicit TextureSettings(ObjectSettings &settings_, DrawWidget &opengl,
                           QWidget *parent = nullptr);
  ~TextureSettings();

 private:
  Ui::TextureSettings *ui_;
  DrawWidget *opengl_;
  ObjectSettings *settings_;

 private slots:
  void LoadTexture();
  void UnloadTexture();
  void LoadStatusUv();
  void SaveUvMap();
};
}  // namespace s21
#endif  // TEXTURESETTINGS_H
