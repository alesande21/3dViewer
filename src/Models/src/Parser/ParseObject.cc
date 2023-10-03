//
// Created by Alesander Britni on 9/19/23.
//

#include "../../include/Parser/ParseObject.h"

namespace s21 {

ParseObject::data_type ParseObject::Parser(std::string name_file) {
  std::ifstream file(name_file);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << name_file << std::endl;
    throw std::invalid_argument("Invalid file extension");
  }

  ClearData();
  std::string line;
  while (std::getline(file, line)) {
    if (line.compare(0, 2, "v ") == 0) {
      ReadVertex(line);
    } else if (line.compare(0, 2, "f ") == 0) {
      FacetsParsing(line);
    } else if (!line.compare(0, 3, "vt ")) {
      TextureParsing(line);
    } else if (!line.compare(0, 3, "vn ")) {
      NormalParsing(line);
    }
  }

  NormalizeVertices(2);
  CreateNormal();

  return data;
}

void ParseObject::NormalParsing(const std::string& line) {
  std::istringstream iss(line);
  std::string remove_char;
  iss >> remove_char;
  Ver3f ver{};
  for (int i = 0; i < 3; i++) {
    iss >> ver[i];
  }

  data.normal_vertex_.push_back(ver);
}

void ParseObject::TextureParsing(const std::string& line) {
  std::istringstream iss(line);
  std::string remove_char;
  iss >> remove_char;
  Ver2f ver{};
  for (int i = 0; i < 2; i++) {
    iss >> ver[i];
  }
  data.texture_vertex_.push_back(ver);
}

void ParseObject::ReadVertex(const std::string& line) {
  std::istringstream iss(line);
  std::string remove_char;
  iss >> remove_char;
  Ver3f ver{};
  for (int i = 0; i < 3; i++) {
    iss >> ver[i];
  }

  data.value_of_vertexes_.push_back(ver);
}

void ParseObject::FacetsParsing(const std::string& line) {
  std::istringstream iss(line);
  iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');

  int vertex_index{};
  std::vector<GLuint> face_indices;
  std::vector<GLuint> texture_indices;
  std::vector<GLuint> normal_indices;

  while (iss >> vertex_index) {
    vertex_index -= 1;
    if (vertex_index < 0) {
      vertex_index += data.value_of_vertexes_.size() + 1;
    }
    face_indices.push_back(vertex_index);

    if (iss.peek() == '/') {
      iss.ignore();
      if (iss.peek() != '/') {
        int texture_index;
        if (!(iss >> texture_index)) {
          continue;
        }
        texture_indices.push_back(texture_index - 1);
      }
      if (iss.peek() == '/') {
        iss.ignore();
        int normal_index;
        if (!(iss >> normal_index)) {
          continue;
        }
        normal_indices.push_back(normal_index - 1);
      }
    }

    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
  }
  for (size_t i = 2; i < face_indices.size(); i++) {
    data.index_triangles_.push_back(face_indices[0]);
    data.index_triangles_.push_back(face_indices[i - 1]);
    data.index_triangles_.push_back(face_indices[i]);

    if (texture_indices.size() == face_indices.size()) {
      data.index_texture_.push_back(texture_indices[0]);
      data.index_texture_.push_back(texture_indices[i - 1]);
      data.index_texture_.push_back(texture_indices[i]);
    }

    if (normal_indices.size() == face_indices.size()) {
      data.index_normal_.push_back(normal_indices[0]);
      data.index_normal_.push_back(normal_indices[i - 1]);
      data.index_normal_.push_back(normal_indices[i]);
    }
  }

  if (face_indices.size() >= 2) {
    for (size_t i = 1; i < face_indices.size(); ++i) {
      data.index_lines_.push_back(face_indices[i - 1]);
      data.index_lines_.push_back(face_indices[i]);
    }
    data.index_lines_.push_back(face_indices.back());
    data.index_lines_.push_back(face_indices.front());
  }
  data.count_facets += 1;
}

void ParseObject::CreateNormal() {
  if (data.value_of_vertexes_.empty() || data.index_triangles_.empty()) return;

  if (data.own_normal_vertex_.size() != data.value_of_vertexes_.size()) {
    data.own_normal_vertex_.resize(data.value_of_vertexes_.size(),
                                   Ver3f(0.0f, 0.0f, 0.0f));
  }

  for (size_t i = 0; i < data.index_triangles_.size(); i += 3) {
    const Ver3f v1_ = data.value_of_vertexes_[data.index_triangles_[i]];
    const Ver3f v2_ = data.value_of_vertexes_[data.index_triangles_[i + 1]];
    const Ver3f v3_ = data.value_of_vertexes_[data.index_triangles_[i + 2]];

    const QVector3D v1 = {v1_.x, v1_.y, v1_.z};
    const QVector3D v2 = {v2_.x, v2_.y, v2_.z};
    const QVector3D v3 = {v3_.x, v3_.y, v3_.z};

    QVector3D side1 = v2 - v1;
    QVector3D side2 = v3 - v1;
    QVector3D normal = side1.crossProduct(side1, side2);

    normal.normalize();

    data.own_normal_vertex_[data.index_triangles_[i]] =
        Ver3f(normal.x(), normal.y(), normal.z());
    data.own_normal_vertex_[data.index_triangles_[i + 1]] =
        Ver3f(normal.x(), normal.y(), normal.z());
    data.own_normal_vertex_[data.index_triangles_[i + 2]] =
        Ver3f(normal.x(), normal.y(), normal.z());
  }
}

void ParseObject::NormalizeVertices(float normalize_size) {
  float min_x = std::numeric_limits<float>::max();
  float min_y = std::numeric_limits<float>::max();
  float min_z = std::numeric_limits<float>::max();
  float max_x = std::numeric_limits<float>::min();
  float max_y = std::numeric_limits<float>::min();
  float max_z = std::numeric_limits<float>::min();
  for (const auto& vertex : data.value_of_vertexes_) {
    min_x = std::min(min_x, vertex.x);
    min_y = std::min(min_y, vertex.y);
    min_z = std::min(min_z, vertex.z);
    max_x = std::max(max_x, vertex.x);
    max_y = std::max(max_y, vertex.y);
    max_z = std::max(max_z, vertex.z);
  }

  auto center_x = (max_x + min_x) / 2.0f;
  auto center_y = (max_y + min_y) / 2.0f;
  auto center_z = (max_z + min_z) / 2.0f;
  auto maxDistance =
      std::max(std::max(max_x - center_x, max_y - center_y), max_z - center_z);

  auto scale_factor = normalize_size / maxDistance;
  for (auto& vertex : data.value_of_vertexes_) {
    vertex.x = (vertex.x - center_x) * scale_factor;
    vertex.y = (vertex.y - center_y) * scale_factor;
    vertex.z = (vertex.z - center_z) * scale_factor;
  }
}

}  // namespace s21
