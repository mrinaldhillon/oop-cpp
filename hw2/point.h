#ifndef POINT_H
#define POINT_H

class Point final {
private:
  double x_, y_;

public:
  Point(double x = 0.0, double y = 0.0);
  double x();
  double y();
  Point& operator=(const Point& rhs);
  double Distance(const Point& from);
};

#endif  // POINT_H
