#include "point.h"
#include <math.h>

namespace polygon {
Point::Point(double x, double y) {
  x_ = x;
  y_ = y;
}

double Point::x() const { return x_; }

double Point::y() const { return y_; }

double Point::Distance(const Point& from) const {
  return sqrt(pow((from.x_ - x_), 2.0) + pow((from.y_ - y_), 2.0));
}

bool Point::operator==(const Point& isEqualTo) const {
  return x_ == isEqualTo.x_ && y_ == isEqualTo.y_ ? true : false;
}
}
