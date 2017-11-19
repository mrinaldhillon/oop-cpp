#include "lib/triangle.h"
#include <math.h>
#include <memory>
#include <string>
#include <vector>
#include "lib/point.h"
// Should <memory> be included here since it has already been included in header

using namespace std;

Triangle::Triangle(unique_ptr<Point> a, unique_ptr<Point> b,
                   unique_ptr<Point> c) {
  a_ = std::move(a);
  b_ = std::move(b);
  c_ = std::move(c);
}

vector<unique_ptr<Point>> Triangle::GetPoints() const {
  vector<unique_ptr<Point>> points;
  points.push_back(make_unique<Point>(*a_));
  points.push_back(make_unique<Point>(*b_));
  points.push_back(make_unique<Point>(*c_));

  // TODO: findout why following does not work
  // vector<unique_ptr<Point>> points = {make_unique<Point>(*a_),
  // make_unique<Point>(*b_), make_unique<Point>(*c_)};
  return points;
}

double Triangle::GetArea() const {
  double ab = a_->Distance(*b_);
  double bc = b_->Distance(*c_);
  double ac = a_->Distance(*c_);
  double s = (ab + bc + ac) / 2.0;
  return sqrt(s * (s - ab) * (s - bc) * (s - ac));
}

const std::string& Triangle::GetType() const { return type_; }
