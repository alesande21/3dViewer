#include "Views/include/MainWindow/MainWindow.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setVersion( 4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
    QApplication a(argc, argv);
    s21::MainWindow w;
    w.show();
    QFile::remove("temp_trans_settings.ini");
    QFile::remove("temp_camera_settings.ini");
    return a.exec();
}
