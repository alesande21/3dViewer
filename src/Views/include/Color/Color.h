#ifndef COLOR_H
#define COLOR_H

#include <QOpenGLFunctions>
#include <QWidget>

#include "../../../Settings/ObjectSettings.h"
#include "../Draw/DrawWidget.h"

namespace Ui {
class Color;
}

namespace s21 {
class Color : public QWidget {
  Q_OBJECT

 public:
  explicit Color(ObjectSettings &settings_, DrawWidget &scene,
                 QWidget *parent = nullptr);
  ~Color();

 private:
  Ui::Color *ui_;
  DrawWidget *scene_;
  ObjectSettings *settings_;

 private slots:
  void ColorBack();
  void ColorLine();
  void ColorVertex();
  void ColorExterior();
  void SizeVertex();
  void WidthLine();
  void LineModeSolid();
  void LineModeStripple();
  void VertexModeNope();
  void VertexModeRound();
  void VertexModeSquare();
  void Primitive();
  void ResetSettings();
  void LoadSettings();
  void LoadLineSettings();
  void LoadVertexSettings();
  void LoadOtherSettings();
};
}  // namespace s21

#endif  // COLOR_H
