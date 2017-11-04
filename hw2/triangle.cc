#include <math.h>
#include "triangle.h"

// This class ingerits from Base and implements fun()
Triangle::Triangle(const Point& a, const Point& b, const Point& c) {
  a_ = a;
  b_ = b;
  c_ = c;
}

vector<Point> Triangle::GetPoints() {
  Point a, b, c;
  a = a_;
  b = b_;
  c = c_;
  vector<Point> points = {a, b, c};
  return points;
}

double Triangle::GetArea() {
  double ab = a_.Distance(b_);
  double bc = b_.Distance(c_);
  double ac = a_.Distance(c_);
  double s = (ab + bc + ac) / 2.0;
  return sqrt(s * (s - ab) * (s - bc) * (s - ac));
}
