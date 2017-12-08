#include "lib/triangle.h"
#include <math.h>
#include <memory>
#include <string>
#include <vector>
#include "lib/point.h"
// Should <memory> be included here since it has already been included in header

using namespace std;

Triangle::Triangle(Point a, Point b, Point c) {
  a_ = a;
  b_ = b;
  c_ = c;
}

const std::vector<Point> Triangle::GetPoints() const {
  return vector<Point>{a_, b_, c_};
}

double Triangle::GetArea() const {
  double ab = a_.Distance(b_);
  double bc = b_.Distance(c_);
  double ac = a_.Distance(c_);
  double s = (ab + bc + ac) / 2.0;
  return sqrt(s * (s - ab) * (s - bc) * (s - ac));
}

const std::string& Triangle::GetType() const { return type_; }
