#include "lib/rectangle_area_calc.h"
#include <math.h>
#include <stdexcept>
#include <vector>

namespace shape {
float RectangleAreaCalc::getArea(std::vector<Point>& points) const {
  if (points.size() != 4)
    throw std::invalid_argument("Invalid number of points in a Rectangle");

  double ab = points.at(0).Distance(points.at(1));
  double ac = points.at(0).Distance(points.at(2));
  double ad = points.at(0).Distance(points.at(3));
  double side1 = 0;
  double side2 = 0;

  if (ab > ac && ab > ad) {
    side1 = ac;
    side2 = ad;
  } else if (ac > ab && ac > ad) {
    side1 = ab;
    side2 = ad;
  } else {
    side1 = ac;
    side2 = ab;
  }
  return side1 * side2;
}

const std::string& RectangleAreaCalc::getType() const { return type_; }
}
