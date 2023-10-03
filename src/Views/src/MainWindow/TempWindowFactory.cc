#include "../../include/MainWindow/TempWindowFactory.h"

namespace s21 {

QWidget* TempWindowFactory::CreateTempWin(int windowType,
                                          ObjectSettings& settings,
                                          DrawWidget* widget) {
  QWidget* window = nullptr;
  switch (windowType) {
    case 0:
      window = new Color(settings, *widget);
      break;
    case 1:
      window = new ParamTransform(*widget);
      break;
    case 2:
      window = new CameraSetting(settings, *widget);
      break;
    case 3:
      window = new LightingSettings(settings, *widget);
      break;
    case 4:
      window = new TextureSettings(settings, *widget);
      break;
  }
  return window;
}

}  // namespace s21
