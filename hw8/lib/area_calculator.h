#ifndef AREA_CALCULATOR_H
#define AREA_CALCULATOR_H

#include <string>
#include <vector>
#include "lib/point.h"

namespace shape {
class AreaCalculator {
 public:
  // Rule of five/six since the base class is intended for polymorphism,
  // virtual destructor had to be declared and so special member functions
  // had to be declared as well, cpp ref rule_of_three
  AreaCalculator(const AreaCalculator&) = default;
  AreaCalculator(AreaCalculator&&) = default;
  AreaCalculator& operator=(const AreaCalculator&) = default;
  AreaCalculator& operator=(AreaCalculator&&) = default;
  AreaCalculator() = default;
  virtual ~AreaCalculator() = default;
  virtual float getArea(std::vector<Point>& points) const = 0;
  virtual const std::string& getType() const = 0;
};
}
#endif  // AREA_CALCULATOR_H
