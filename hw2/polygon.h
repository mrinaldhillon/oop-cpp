#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include <vector>
#include "point.h"
using namespace std;

class Polygon {
 public:
  virtual vector<Point> GetPoints() = 0;
  virtual double GetArea() = 0;
  virtual const string& GetType() = 0;
};

#endif  // POLYGON_H
