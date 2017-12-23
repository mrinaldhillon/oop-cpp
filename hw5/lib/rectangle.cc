#include "lib/rectangle.h"
#include <memory>
#include <string>
#include <vector>
#include "lib/point.h"

using namespace std;

namespace polygon {
Rectangle::Rectangle(Point a, Point b, Point c, Point d) {
  a_ = a;
  b_ = b;
  c_ = c;
  d_ = d;
}

const std::vector<Point> Rectangle::GetPoints() const {
  return vector<Point>{a_, b_, c_, d_};
}

double Rectangle::GetArea() const {
  double ab = a_.Distance(b_);
  double ac = a_.Distance(c_);
  double ad = a_.Distance(d_);
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

const std::string& Rectangle::GetType() const { return type_; }
}
