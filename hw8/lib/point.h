#ifndef POINT_H
#define POINT_H

namespace shape {

class Point final {
 private:
  double x_ = 0.0, y_ = 0.0;

 public:
  Point(double x = 0.0, double y = 0.0);

  double x() const;
  double y() const;
  double Distance(const Point& from) const;
  bool operator==(const Point& isEqualTo) const;
};
}

#endif  // POINT_H
