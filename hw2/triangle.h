#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"

// This class ingerits from Base and implements fun()
class Triangle : public Polygon {
 private:
  Point a_, b_, c_;

 public:
  Triangle(const Point& a, const Point& b, const Point& c);
  vector<Point> GetPoints();
  double GetArea();
};

#endif // TRIANGLE_H
