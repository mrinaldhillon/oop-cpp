#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libpolygon.h"

using namespace std;

namespace {
using namespace polygon;

TEST(RectangleTest, IsTypeRectangle) {
  Rectangle target{{-6, 2}, {-3, 6}, {9, -3}, {6, -7}};
  EXPECT_THAT(target.GetType(), ::testing::StrEq("Rectangle"));
}

TEST(RectangleTest, GetPoints) {
  Point a{-6, 2};
  Point b{-3, 6};
  Point c{9, -3};
  Point d{6, -7};

  Rectangle target{a, b, c, d};
  const vector<polygon::Point> actual_points = target.GetPoints();
  vector<polygon::Point> expected_points{a, b, c, d};
  EXPECT_THAT(actual_points, ::testing::ContainerEq(expected_points));
}

TEST(RectangleTest, GetArea) {
  Rectangle target{{-6, 2}, {-3, 6}, {9, -3}, {6, -7}};
  EXPECT_EQ(target.GetArea(), 75.0);
}

TEST(TriangleTest, IsTypeTriangle) {
  Triangle target{Point{15, 5}, Point{23, 30}, Point{50, 25}};
  EXPECT_THAT(target.GetType(), ::testing::StrEq("Triangle"));
}

TEST(TriangleTest, GetPoints) {
  Point a{15, 5};
  Point b{23, 30};
  Point c{50, 25};

  Triangle target{a, b, c};
  const vector<polygon::Point> actual_points = target.GetPoints();
  vector<polygon::Point> expected_points{a, b, c};
  EXPECT_THAT(actual_points, ::testing::ContainerEq(expected_points));
}

TEST(TriangleTest, GetArea) {
  Triangle target{Point{15, 5}, Point{23, 30}, Point{50, 25}};
  EXPECT_EQ(target.GetArea(), 357.50000000000017);
}
}
