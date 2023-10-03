//
// Created by Alesander Britni on 8/23/23.
//

#ifndef INC_3D_TEST_PARSEOBJECT_H
#define INC_3D_TEST_PARSEOBJECT_H

#include <QVector3D>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#ifdef _WIN32
#include <GL/gl.h>
#elif __APPLE__
#include <OpenGL/gl.h>
#endif

#include "../Types/s21_Ver2f.h"
#include "../Types/s21_Ver3f.h"

namespace s21 {
class ParseObject {
 private:
  struct Data;

 public:
  using size_type = size_t;
  using data_type = s21::ParseObject::Data;
  using ver3f_type = s21::Ver3f;
  using ver2f_type = s21::Ver2f;

  Data Parser(std::string name_file);
  inline void ClearData() { data.Clear(); }

 private:
  struct Data {
    std::vector<GLuint> index_triangles_{};
    std::vector<GLuint> index_lines_{};
    std::vector<GLuint> index_normal_{};
    std::vector<GLuint> index_texture_{};
    std::vector<Ver2f> texture_vertex_{};
    std::vector<Ver3f> normal_vertex_{};
    std::vector<Ver3f> own_normal_vertex_{};
    std::vector<Ver3f> value_of_vertexes_{};
    size_t count_facets{};

    void Clear() {
      index_triangles_.clear();
      value_of_vertexes_.clear();
      index_lines_.clear();
      normal_vertex_.clear();
      texture_vertex_.clear();
      own_normal_vertex_.clear();
      index_normal_.clear();
      index_texture_.clear();
      count_facets = 0;
    }
  };

  Data data{};

  void NormalParsing(const std::string& line);
  void TextureParsing(const std::string& line);
  void ReadVertex(const std::string& line);
  void FacetsParsing(const std::string& line);
  void NormalizeVertices(float normalize_size);
  void CreateNormal();
};
}  // namespace s21

#endif  // INC_3D_TEST_PARSEOBJECT_H
