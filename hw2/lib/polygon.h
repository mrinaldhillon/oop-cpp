#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include <vector>
#include "point.h"
using namespace std;

class Polygon {
 public:
  // TBD: virtual destructor just works, not sure if this the best practice for
  // base class
  virtual ~Polygon() {}
  virtual vector<Point> GetPoints() = 0;
  virtual double GetArea() = 0;
  virtual const string& GetType() = 0;
};

#endif  // POLYGON_H
