//
// Created by Alesander Britni on 8/22/23.
//

#ifndef INC_3D_TEST_S21_FAC3F_H
#define INC_3D_TEST_S21_FAC3F_H

#ifdef _WIN32
#include <GL/gl.h>
#elif __APPLE__
#include <OpenGL/gl.h>
#endif

namespace s21 {

struct Fac3f {
  std::vector<GLuint> facets_{};
  std::vector<GLuint> texture_{};
  std::vector<GLuint> normal_{};
};

}  // namespace s21

#endif  // INC_3D_TEST_S21_FAC3F_H
