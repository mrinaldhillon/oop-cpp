#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <memory>
#include <string>
#include <vector>
#include "lib/point.h"
#include "lib/polygon.h"

class Rectangle final : public Polygon {
 private:
  std::unique_ptr<Point> a_, b_, c_, d_;
  const std::string type_ = "Rectangle";

 public:
  Rectangle(std::unique_ptr<Point> a, std::unique_ptr<Point> b,
            std::unique_ptr<Point> c, std::unique_ptr<Point> d);
  std::vector<std::unique_ptr<Point>> GetPoints() const;
  double GetArea() const;
  // TBD: typeid(self).name() would've produce same result prefixed with class
  // id and but with overhead
  const std::string& GetType() const;
};

#endif  // RECTANGLE_H
