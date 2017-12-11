#ifndef RECTANGLE_AREA_CALC_H
#define RECTANGLE_AREA_CALC_H

#include <vector>
#include "lib/area_calculator.h"

namespace shape {
class RectangleAreaCalc : public AreaCalculator {
 private:
  const std::string type_ = "Rectangle";

 public:
  float getArea(std::vector<Point>& points) const;
  const std::string& getType() const;
};
}

#endif  // RECTANGLE_AREA_CALC_H
