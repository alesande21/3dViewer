#ifndef PARAMTRANSFORM_H
#define PARAMTRANSFORM_H

#include <QWidget>

#include "../../../Controlers/include/ObjectController.h"
#include "../Draw/DrawWidget.h"

namespace Ui {
class ParamTransform;
}
namespace s21 {
class ParamTransform : public QWidget {
  Q_OBJECT

 public:
  explicit ParamTransform(DrawWidget &opengl, QWidget *parent = nullptr);
  ~ParamTransform();

 private:
  Ui::ParamTransform *ui_;
  DrawWidget *opengl_;

 private slots:
  void RotX();
  void RotY();
  void RotZ();
  void TransX();
  void TransY();
  void TransZ();
  void Scale();
  void SaveTempSettings();
  void LoadTempSettings();
};
}  // namespace s21
#endif  // PARAMTRANSFORM_H
