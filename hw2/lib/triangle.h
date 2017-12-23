#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <memory>
#include <string>
#include <vector>
#include "lib/point.h"
#include "lib/polygon.h"

class Triangle final : public Polygon {
 private:
  Point a_, b_, c_;
  const std::string type_ = "Triangle";

 public:
  Triangle(Point a, Point b, Point c);
 const std::vector<Point> GetPoints() const;
  double GetArea() const;
  // TODO: typeid(self).name() would've produce same result prefixed with class
  // id and with overhead
  const std::string& GetType() const;
};

#endif  // TRIANGLE_H
