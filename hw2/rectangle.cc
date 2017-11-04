#include "rectangle.h"
#include <math.h>
#include <iostream>
using namespace std;

// This class ingerits from Base and implements fun()
Rectangle::Rectangle(const Point& a, const Point& b, const Point& c,
                     const Point& d) {
  a_ = a;
  b_ = b;
  c_ = c;
  d_ = d;
}

vector<Point> Rectangle::GetPoints() {
  Point a, b, c, d;
  a = a_;
  b = b_;
  c = c_;
  d = d_;
  vector<Point> points = {a, b, c, d};
  return points;
}

double Rectangle::GetArea() {
  double ab = a_.Distance(b_);
  double ac = a_.Distance(c_);
  double ad = a_.Distance(d_);
  double bc = b_.Distance(c_);
  double bd = b_.Distance(d_);
  double cd = c_.Distance(d_);
  double side1 = 0;
  double side2 = 0;

  if (ab > ac && ab > ad) {
    side1 = ac;
    side2 = ad;
  } else if (ac > ab && ac > ad) {
    side1 = ab;
    side2 = ad;
  } else {
    side1 = ac;
    side2 = ab;
  }
  return side1 * side2;
}
