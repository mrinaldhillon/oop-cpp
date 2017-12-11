#include "lib/triangle_area_calc.h"
#include <math.h>
#include <stdexcept>
#include <vector>

namespace shape {
float TriangleAreaCalc::getArea(std::vector<Point>& points) const {
  if (points.size() != 3)
    throw std::invalid_argument("Invalid number of points in a Triangle");

  double ab = points.at(0).Distance(points.at(1));
  double bc = points.at(1).Distance(points.at(2));
  double ac = points.at(0).Distance(points.at(2));
  double s = (ab + bc + ac) / 2.0;
  return sqrt(s * (s - ab) * (s - bc) * (s - ac));
}

const std::string& TriangleAreaCalc::getType() const { return type_; }
}
