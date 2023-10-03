#include "../../include/MainWindow/MainWindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  setWindowTitle("3DViewer_v2.0");
  setGeometry(1000, 1000, 1500, 1000);
  settings_.LoadSettings();
  ui_->widget->SetSettings(settings_);
  SetParamObj("");
  connect(ui_->call_color_ui, &QPushButton::clicked,
          [this]() { OpenTempWindow(0); });
  connect(ui_->call_transform_ui, &QPushButton::clicked,
          [this]() { OpenTempWindow(1); });
  connect(ui_->call_camera_ui, &QPushButton::clicked,
          [this]() { OpenTempWindow(2); });

  connect(ui_->call_light_ui, &QPushButton::clicked,
          [this]() { OpenTempWindow(3); });
  connect(ui_->call_texture_ui, &QPushButton::clicked,
          [this]() { OpenTempWindow(4); });

  connect(ui_->open_file, SIGNAL(triggered()), this, SLOT(OpenFile()));
  connect(ui_->save_settings, SIGNAL(triggered()), this, SLOT(SaveSettings()));
  connect(ui_->load_settings, SIGNAL(triggered()), this, SLOT(LoadSettings()));
  connect(ui_->image, SIGNAL(triggered()), this, SLOT(SaveImage()));
  connect(ui_->gif, SIGNAL(triggered()), this, SLOT(SaveGif()));
  connect(ui_->auto_rtn, SIGNAL(triggered()), this, SLOT(AutoRotateObj()));
}

MainWindow::~MainWindow() {
  settings_.SaveSettings();
  delete ui_;
}

void MainWindow::OpenTempWindow(int num_window) {
  static int prev_window = 7;
  if (ui_->horizontalLayout_2->indexOf(window_) != -1) {
    ui_->horizontalLayout_2->removeWidget(window_);
    window_->hide();
    delete window_;
    window_ = nullptr;
  } else {
    prev_window = 7;
  }

  if (window_ == nullptr && prev_window != num_window) {
    prev_window = num_window;
    window_ =
        TempWindowFactory::CreateTempWin(num_window, settings_, ui_->widget);
    ui_->horizontalLayout_2->addWidget(window_);
    window_->show();
  }
}

void MainWindow::OpenFile() {
  QString file =
      QFileDialog::getOpenFileName(this, "Upload file ", "", "OBJ (*.obj)");
  if (!file.isEmpty()) {
    QFile::remove("temp_trans_settings.ini");
    QFile::remove("temp_camera_settings.ini");
    ui_->widget->SendController().DeleteTexture();
    settings_.SaveSettings();
    settings_.LoadSettings();
    ui_->widget->SendController().UploadObjectFromFile(
        file.toUtf8().constData());
    SetParamObj(file.toUtf8().constData());
    ui_->widget->update();
  }
}

void MainWindow::SaveSettings() { settings_.SaveSettings(); }

void MainWindow::LoadSettings() {
  settings_.LoadSettings();
  ui_->widget->update();
}

void MainWindow::SaveImage() {
  QString filepath = QFileDialog::getSaveFileName(
      this, "Save as...", "screen.bmp", "Images (*.bmp *.jpeg)");
  if (!filepath.isEmpty()) {
    media_controller_.SaveImage(filepath, ui_->widget);
  }
}

void MainWindow::SaveGif() {
  QString filepath = QFileDialog::getSaveFileName(
      this, "Save as...", "animation.gif", "GIF (*.gif)");
  if (!filepath.isEmpty()) {
    media_controller_.SaveGif(filepath, ui_->widget);
  }
}

void MainWindow::SetParamObj(std::string name) {
  int r = 255 - settings_.color_back_.x();
  int g = 255 - settings_.color_back_.y();
  int b = 255 - settings_.color_back_.z();
  QString style_sheet =
      QString("color: rgba(%1, %2, %3, 0.6)").arg(r).arg(g).arg(b);
  if (name.length() != 0) {
    std::filesystem::path pathObj(name);
    std::string fileName = pathObj.filename().string();

    auto facet_count = ui_->widget->SendController().GetObject().count_facets;
    auto vertex_count =
        ui_->widget->SendController().GetObject().value_of_vertexes_.size();
    QString text = QString("название: %1  /  вершины: %2  /  ребера: %3")
                       .arg(fileName.c_str())
                       .arg(vertex_count)
                       .arg(facet_count);
    ui_->name_obj->setText(text);
    ui_->name_obj->setStyleSheet(style_sheet);
  } else {
    ui_->name_obj->setText("Нет объекта");
    ui_->name_obj->setStyleSheet(style_sheet);
  }
}

void MainWindow::AutoRotateObj() {
  QElapsedTimer timer;
  timer.start();

  float rtn_curr = 0.0f;
  float time_elapsed = 0.0f;
  static float rtn_prev = 0.0f;

  while (time_elapsed < 10000) {
    QCoreApplication::processEvents();
    time_elapsed = static_cast<float>(timer.elapsed());
    rtn_curr += 0.1f;
    ui_->widget->SendController().RotationX(rtn_prev, rtn_curr);
    rtn_prev = rtn_curr;
    ui_->widget->update();
  }
}

}  // namespace s21
