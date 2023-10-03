#ifndef LIGHTINGSETTINGS_H
#define LIGHTINGSETTINGS_H

#include <QWidget>

#include "../../../Settings/ObjectSettings.h"
#include "../Draw/DrawWidget.h"

namespace Ui {
class LightingSettings;
}

namespace s21 {
class LightingSettings : public QWidget {
  Q_OBJECT

 public:
  explicit LightingSettings(ObjectSettings &settings_, DrawWidget &opengl,
                            QWidget *parent = nullptr);
  ~LightingSettings();

 private:
  Ui::LightingSettings *ui_;
  DrawWidget *opengl_;
  ObjectSettings *settings_;

 private slots:
  void ModeCarcass();
  void ModeFlat();
  void ModeSmooth();
  void LightCoordinate();
  void AmbientStrenght();
  void SpecularStrenght();
  void TypeAmbient();
  void TypeSpecular();
  void LightColor();
  void LoadTempSettings();
};
}  // namespace s21
#endif  // LIGHTINGSETTINGS_H
