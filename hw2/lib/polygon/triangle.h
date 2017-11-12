#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"

class Triangle final : public Polygon {
 private:
  Point a_, b_, c_;
  const string type_ = "Triangle";

 public:
  Triangle(const Point& a, const Point& b, const Point& c);
  vector<Point> GetPoints();
  double GetArea();
  // TODO: typeid(self).name() would've produce same result prefixed with class
  // id and with overhead
  const string& GetType() { return type_; }
};

#endif  // TRIANGLE_H
