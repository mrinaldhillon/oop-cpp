#ifndef TRIANGLE_AREA_CALC_H
#define TRIANGLE_AREA_CALC_H

#include <vector>
#include "lib/area_calculator.h"

namespace shape {
class TriangleAreaCalc : public AreaCalculator {
 private:
  const std::string type_ = "Triangle";

 public:
  float getArea(std::vector<Point>& points) const;
  const std::string& getType() const;
};
}

#endif  // TRIANGLE_AREA_CALC_H
