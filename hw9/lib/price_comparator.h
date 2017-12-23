#ifndef PRICE_COMPARATOR_H
#define PRICE_COMPARATOR_H

#include "lib/car.h"

namespace car {
namespace comparator {

struct {
  bool operator()(const Car& car1, const Car& car2) const {
    return car1.price() < car2.price();
  }
} PriceComparator;

}  // end of namespace comparator
}  // end of namespace car

#endif  // PRICE_COMPARATOR_H
