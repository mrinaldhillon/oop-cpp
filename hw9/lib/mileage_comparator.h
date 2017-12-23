#ifndef MILEAGE_COMPARATOR_H
#define MILEAGE_COMPARATOR_H

#include "lib/car.h"

namespace car {
namespace comparator {

struct {
  bool operator()(const Car& car1, const Car& car2) const {
    return car1.mileage() < car2.mileage();
  }
} MileageComparator;

}  // end of namespace comparator
}  // end of namespace car
#endif  // MILEAGE_COMPARATOR_H
