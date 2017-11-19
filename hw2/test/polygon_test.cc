#include <iostream>
#include <memory>
#include <vector>
#include "lib/libpolygon.h"

using namespace std;

void PolygonClassTest() {
  vector<unique_ptr<Polygon>> polygons;

  polygons.push_back(make_unique<Triangle>(make_unique<Point>(0, 0),
                                           make_unique<Point>(2, 2),
                                           make_unique<Point>(1, 3)));
  polygons.push_back(make_unique<Triangle>(make_unique<Point>(15, 5),
                                           make_unique<Point>(23, 30),
                                           make_unique<Point>(50, 25)));
  polygons.push_back(make_unique<Rectangle>(
      make_unique<Point>(-6, 2), make_unique<Point>(-3, 6),
      make_unique<Point>(9, -3), make_unique<Point>(6, -7)));
  polygons.push_back(make_unique<Rectangle>(
      make_unique<Point>(-3, -4), make_unique<Point>(-1, 2),
      make_unique<Point>(2, 1), make_unique<Point>(0, -5)));

  for (const auto& polygon : polygons) {
    cout << polygon->GetType() << ":\n";
    cout << "Coordinates:";
    vector<unique_ptr<Point>> points = polygon->GetPoints();
    for (const auto& point : points) {
      cout << " (" << point->x() << "," << point->y() << ")";
    }
    cout << endl;
    cout << "Area: " << polygon->GetArea() << endl;
  }
}

int main() {
  PolygonClassTest();
  return 0;
}
