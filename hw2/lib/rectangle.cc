#include "lib/rectangle.h"
#include <memory>
#include <string>
#include <vector>
#include "lib/point.h"

using namespace std;

Rectangle::Rectangle(std::unique_ptr<Point> a, std::unique_ptr<Point> b,
                     std::unique_ptr<Point> c, std::unique_ptr<Point> d) {
  a_ = std::move(a);
  b_ = std::move(b);
  c_ = std::move(c);
  d_ = std::move(d);
}

vector<std::unique_ptr<Point>> Rectangle::GetPoints() const {
  vector<unique_ptr<Point>> points;
  points.push_back(make_unique<Point>(*a_));
  points.push_back(make_unique<Point>(*b_));
  points.push_back(make_unique<Point>(*c_));
  points.push_back(make_unique<Point>(*d_));

  // TODO: findout why following does not work
  // vector<unique_ptr<Point>> points = {make_unique<Point>(*a_),
  // make_unique<Point>(*b_), make_unique<Point>(*c_)};
  return points;
}

double Rectangle::GetArea() const {
  double ab = a_->Distance(*b_);
  double ac = a_->Distance(*c_);
  double ad = a_->Distance(*d_);
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
