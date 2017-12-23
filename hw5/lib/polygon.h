#ifndef POLYGON_H
#define POLYGON_H

#include <memory>
#include <string>
#include <vector>
#include "lib/point.h"

namespace polygon {
class Polygon {
 public:
  virtual ~Polygon() {}
  virtual const std::vector<Point> GetPoints() const = 0;
  virtual double GetArea() const = 0;
  virtual const std::string& GetType() const = 0;
};
}

#endif  // POLYGON_H
