#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygon.h"

// This class ingerits from Base and implements fun()
class Rectangle : public Polygon {
 private:
  Point a_, b_, c_, d_;

 public:
  Rectangle(const Point& a, const Point& b, const Point& c, const Point& d);
  vector<Point> GetPoints();
  double GetArea();
};

#endif  // RECTANGLE_H
