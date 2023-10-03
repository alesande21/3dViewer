#include <gtest/gtest.h>

#include "../Models/include/Parser/ParseObject.h"

class ParseObjectTest : public ::testing::Test {
 protected:
  s21::ParseObject parser;
};

TEST_F(ParseObjectTest, FileNotFound) {
  ASSERT_THROW(parser.Parser("../2.obj"), std::invalid_argument);
}

TEST_F(ParseObjectTest, ValidFileParsing) {
  s21::ParseObject::data_type data = parser.Parser("../1.obj");

  ASSERT_EQ(data.index_triangles_.size(), 36);
  ASSERT_EQ(data.value_of_vertexes_.size(), 24);
}

TEST_F(ParseObjectTest, ClearData) {
  s21::ParseObject::data_type data = parser.Parser("../1.obj");
  data.Clear();

  ASSERT_EQ(data.index_triangles_.size(), 0);
  ASSERT_EQ(data.value_of_vertexes_.size(), 0);
}