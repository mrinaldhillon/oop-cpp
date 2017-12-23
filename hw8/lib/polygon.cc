#include "lib/polygon.h"

using namespace std;

namespace shape {
Polygon::Polygon(std::unique_ptr<std::vector<Point>> points,
                 std::unique_ptr<AreaCalculator> area_calc)
    : points_(std::move(points)), area_calc_(std::move(area_calc)) {}

void Polygon::setAreaCalc(std::unique_ptr<AreaCalculator> area_calc) {
  area_calc_ = std::move(area_calc);
}

void Polygon::addPoint(Point point) { points_->push_back(point); }

void Polygon::removePoint() { points_->pop_back(); }

float Polygon::getArea() const { return area_calc_->getArea(*points_); }

const std::string& Polygon::getType() const { return area_calc_->getType(); }
}
