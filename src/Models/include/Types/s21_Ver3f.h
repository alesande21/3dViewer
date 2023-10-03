//
// Created by Alesander Britni on 8/22/23.
//

#ifndef INC_3D_TEST_S21_VER3F_H
#define INC_3D_TEST_S21_VER3F_H

#ifdef _WIN32
#include <GL/gl.h>
#elif __APPLE__
#include <OpenGL/gl.h>
#endif

namespace s21 {
struct Ver3f {
  GLfloat x{}, y{}, z{};

  Ver3f() = default;
  //
  Ver3f(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->z = z;
  };
  GLfloat &operator[](int i) {
    if (i == 0) {
      return x;
    } else if (i == 1) {
      return y;
    } else if (i == 2) {
      return z;
    }
    return x;
  }
};
}  // namespace s21

#endif  // INC_3D_TEST_S21_VER3F_H
