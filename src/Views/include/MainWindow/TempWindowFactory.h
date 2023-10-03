#ifndef TEMPWINDOWFACTORY_H
#define TEMPWINDOWFACTORY_H

#include "../../../Settings/ObjectSettings.h"
#include "../Camera/CameraSetting.h"
#include "../Color/Color.h"
#include "../Draw/DrawWidget.h"
#include "../Light/LightingSettings.h"
#include "../Texture/TextureSettings.h"
#include "../Transformation/ParamTransform.h"

namespace s21 {
class TempWindowFactory {
 public:
  static QWidget* CreateTempWin(int windowType, ObjectSettings& settings,
                                DrawWidget* widget);
};
}  // namespace s21
#endif  // TEMPWINDOWFACTORY_H
