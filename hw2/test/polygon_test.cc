#include <iostream>
#include <memory>
#include <vector>
#include "lib/libpolygon.h"

using namespace std;

void PolygonClassTest() {
  /* vector of unique pointers is not ideal, since the scope is local
 * however abstact class types canot be static allocated i.e. vector<Polygon>
 * won't work
 * but since it vector of abstact class type
 * so in absence of unique pointers i had to heap allocate vector member objects
 * Probably there is a better, will look into later
 */
  vector<unique_ptr<Polygon>> polygons;

  polygons.push_back(
      make_unique<Triangle>(Point(0, 0), Point(2, 2), Point(1, 3)));
  polygons.push_back(
      make_unique<Triangle>(Point(15, 5), Point(23, 30), Point(50, 25)));
  polygons.push_back(make_unique<Rectangle>(Point(-6, 2), Point(-3, 6),
                                            Point(9, -3), Point(6, -7)));
  polygons.push_back(make_unique<Rectangle>(Point(-3, -4), Point(-1, 2),
                                            Point(2, 1), Point(0, -5)));

  for (const auto& polygon : polygons) {
    cout << polygon->GetType() << ":\n";
    cout << "Coordinates:";
    vector<Point> points = polygon->GetPoints();
    for (auto point : points) {
      cout << " (" << point.x() << "," << point.y() << ")";
    }
    cout << endl;
    cout << "Area: " << polygon->GetArea() << endl;
  }
}

int main() {
  PolygonClassTest();
  return 0;
}
