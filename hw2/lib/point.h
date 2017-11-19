#ifndef POINT_H
#define POINT_H

class Point final {
private:
  double x_= 0.0, y_ = 0.0;

public:
  Point(double x = 0.0, double y = 0.0);
  double x();
  double y();
  double Distance(const Point& from);
};

#endif  // POINT_H
