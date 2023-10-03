#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QMainWindow>
#include <QStackedLayout>

#include "../../../Controlers/include/MediaController.h"
#include "../../../Settings/ObjectSettings.h"
#include "../Camera/CameraSetting.h"
#include "../Color/Color.h"
#include "../Draw/DrawWidget.h"
#include "../Light/LightingSettings.h"
#include "../Texture/TextureSettings.h"
#include "../Transformation/ParamTransform.h"
#include "TempWindowFactory.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui_;
  ObjectSettings settings_;
  MediaController media_controller_;
  QWidget *window_{};

 private slots:
  void OpenFile();
  void SaveSettings();
  void LoadSettings();
  void SaveImage();
  void SaveGif();
  void SetParamObj(std::string name);
  void OpenTempWindow(int num_window);
  void AutoRotateObj();
};
}  // namespace s21

#endif  // MAINWINDOW_H
