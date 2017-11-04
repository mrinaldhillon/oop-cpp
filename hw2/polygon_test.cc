#include "polygon.h"
#include <iostream>
#include <typeinfo>
#include "point.h"
#include "rectangle.h"
#include "triangle.h"

using namespace std;

void PointClassTest() {
  Point a(2, 4);
  Point b(4, 6);
  cout << "Distance of a from b = " << a.Distance(b) << endl;
}

void PolygonClassTest() {
  vector<Polygon *> polygons;

  polygons.push_back(new Triangle(Point(0, 0), Point(2, 2), Point(1, 3)));
  polygons.push_back(new Triangle(Point(15, 5), Point(23, 30), Point(50, 25)));
  polygons.push_back(
      new Rectangle(Point(-6, 2), Point(-3, 6), Point(9, -3), Point(6, -7)));
  polygons.push_back(
      new Rectangle(Point(-3, -4), Point(-1, 2), Point(2, 1), Point(0, -5)));

  for (Polygon *polygon : polygons) {
    if (typeid(Triangle) == typeid(*polygon)) {
      cout << "Triangle:\n";
    } else
      cout << "Rectangle:\n";
    cout << "Coordinates:";
    vector<Point> points = polygon->GetPoints();
    for (Point point : points) {
      cout << " (" << point.x() << "," << point.y() << ")";
    }
    cout << endl;
    cout << "Area: " << polygon->GetArea() << endl;
  }

  for (Polygon *polygon : polygons) {
    delete polygon;
  }
}

int main() {
  // PointClassTest();
  PolygonClassTest();
  return 0;
}
