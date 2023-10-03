//
// Created by Alesander Britni on 8/22/23.
//

#ifndef INC_3D_TEST_S21_VER2F_H
#define INC_3D_TEST_S21_VER2F_H

#ifdef _WIN32
#include <GL/gl.h>
#elif __APPLE__
#include <OpenGL/gl.h>
#endif

namespace s21 {

struct Ver2f {
  GLfloat u{}, v{};

  GLfloat &operator[](int i) {
    if (i == 0) {
      return u;
    } else if (i == 1) {
      return v;
    }
    return u;
  }
};
}  // namespace s21

#endif  // INC_3D_TEST_S21_VER2F_H
