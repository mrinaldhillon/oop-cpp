#include <memory>
#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libpolygon.h"
using namespace std;

namespace {
using namespace shape;

class RectangleTest : public ::testing::Test {
 protected:
  Polygon rectangle_{
      make_unique<vector<Point>>(vector<Point>(
          {Point{-6, 2}, Point{-3, 6}, Point{9, -3}, Point{6, -7}})),
      make_unique<RectangleAreaCalc>()};
};

class TriangleTest : public ::testing::Test {
 protected:
  Polygon triangle_{make_unique<vector<Point>>(vector<Point>(
                        {Point{15, 5}, Point{23, 30}, Point{50, 25}})),
                    make_unique<TriangleAreaCalc>()};
};

TEST(PolygonTest, rectangleInstantiation) {
  Polygon polygon{
      make_unique<vector<Point>>(vector<Point>(
          {Point{-6, 2}, Point{-3, 6}, Point{9, -3}, Point{6, -7}})),
      make_unique<RectangleAreaCalc>()};
  EXPECT_THAT(polygon.getType(), ::testing::StrEq("Rectangle"));
}

TEST_F(RectangleTest, getArea) { EXPECT_FLOAT_EQ(rectangle_.getArea(), 75.0); };

TEST_F(RectangleTest, getAreaThrowsInvalidArgumentUponIncorrectVectices) {
  rectangle_.removePoint();
  EXPECT_THROW(rectangle_.getArea(), invalid_argument);
}

TEST_F(RectangleTest, tranformRectangleToTriangleTest) {
  EXPECT_THAT(rectangle_.getType(), ::testing::StrEq("Rectangle"));
  rectangle_.removePoint();
  rectangle_.setAreaCalc(make_unique<TriangleAreaCalc>());
  EXPECT_THAT(rectangle_.getType(), ::testing::StrEq("Triangle"));
}

TEST(PolygonTest, triangleInstantiation) {
  Polygon polygon{make_unique<vector<Point>>(vector<Point>(
                      {Point{15, 5}, Point{23, 30}, Point{50, 25}})),
                  make_unique<TriangleAreaCalc>()};
  EXPECT_THAT(polygon.getType(), ::testing::StrEq("Triangle"));
}

TEST_F(TriangleTest, getArea) {
  EXPECT_FLOAT_EQ(triangle_.getArea(), 357.50000000000017);
};

TEST_F(TriangleTest, getAreaThrowsInvalidArgumentUponIncorrectVectices) {
  triangle_.removePoint();
  EXPECT_THROW(triangle_.getArea(), invalid_argument);
};

TEST_F(TriangleTest, tranformTriangleToRectangleTest) {
  EXPECT_THAT(triangle_.getType(), ::testing::StrEq("Triangle"));
  triangle_.addPoint(Point{2, 7});
  triangle_.setAreaCalc(make_unique<RectangleAreaCalc>());
  EXPECT_THAT(triangle_.getType(), ::testing::StrEq("Rectangle"));
}
}
