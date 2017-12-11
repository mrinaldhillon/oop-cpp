#ifndef YEAR_COMPARATOR_H
#define YEAR_COMPARATOR_H

#include "lib/car.h"

namespace car {
namespace comparator {

struct {
  bool operator()(const Car& car1, const Car& car2) const {
    return car1.year() > car2.year();
  }
} YearComparator;

}  // end of namespace comparator
}  // end of namespace car

#endif  // YEAR_COMPARATOR_H
