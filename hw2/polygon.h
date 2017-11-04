#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "point.h"
using namespace std;

class Polygon {
 public:
  virtual vector<Point> GetPoints() = 0;
  virtual double GetArea() = 0;
  //virtual Point GetCentroid() = 0;
};

#endif // POLYGON_H
