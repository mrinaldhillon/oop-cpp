#include "lib/car.h"

namespace car {

int Car::price() const { return price_; }
int Car::year() const { return year_; }
float Car::mileage() const { return mileage_; }

bool Car::operator==(const Car& rhs) const {
  return price_ == rhs.price() && year_ == rhs.year() &&
         mileage_ == rhs.mileage();
}

}  // end of namespace car
