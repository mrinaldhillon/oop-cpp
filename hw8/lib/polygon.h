#ifndef POLYGON_H
#define POLYGON_H

#include <memory>
#include <string>
#include <vector>
#include "lib/area_calculator.h"
#include "lib/point.h"

namespace shape {
class Polygon {
 private:
  std::unique_ptr<std::vector<Point>> points_;
  std::unique_ptr<AreaCalculator> area_calc_;

 public:
  Polygon(std::unique_ptr<std::vector<Point>> points,
          std::unique_ptr<AreaCalculator> area_calc);
  ~Polygon() = default;
  void setAreaCalc(std::unique_ptr<AreaCalculator> area_calc);
  void addPoint(Point point);
  void removePoint();
  float getArea() const;
  const std::string& getType() const;
};
}

#endif  // POLYGON_H
