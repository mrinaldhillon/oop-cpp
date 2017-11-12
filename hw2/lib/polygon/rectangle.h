#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygon.h"

class Rectangle final : public Polygon {
 private:
  Point a_, b_, c_, d_;
  const string type_ = "Rectangle";

 public:
  Rectangle(const Point& a, const Point& b, const Point& c, const Point& d);
  vector<Point> GetPoints();
  double GetArea();
  // TODO: typeid(self).name() would've produce same result prefixed with class
  // id and but with overhead
  const string& GetType() { return type_; }
};

#endif  // RECTANGLE_H
