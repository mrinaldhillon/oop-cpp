#include <algorithm>
#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libcar_comparator.h"

namespace car {
namespace comparator{
namespace {

class ComparatorTest : public ::testing::Test {
 protected:
  std::vector<Car> cars_{Car{3000, 2010, 5200}, car::Car{1000, 1995, 11000},
                    Car{2000, 2000, 12000}, Car{4000, 2005, 3200}};
  std::vector<Car> sorted_by_price_{Car{1000, 1995, 11000}, Car{2000, 2000, 12000},
                               Car{3000, 2010, 5200}, Car{4000, 2005, 3200}};
  std::vector<Car> sorted_by_mileage_{Car{4000, 2005, 3200}, Car{3000, 2010, 5200},
                                 Car{1000, 1995, 11000},
                                 Car{2000, 2000, 12000}};
  std::vector<Car> sorted_by_year_{Car{3000, 2010, 5200}, Car{4000, 2005, 3200},
                              Car{2000, 2000, 12000}, Car{1000, 1995, 11000}};
};

TEST_F(ComparatorTest, PriceComparator) {
  sort(cars_.begin(), cars_.end(), PriceComparator);
  EXPECT_THAT(cars_, ::testing::ContainerEq(sorted_by_price_));
}

TEST_F(ComparatorTest, YearComparator) {
  sort(cars_.begin(), cars_.end(), YearComparator);
  EXPECT_THAT(cars_, ::testing::ContainerEq(sorted_by_year_));
}

TEST_F(ComparatorTest, MileageComparator) {
  sort(cars_.begin(), cars_.end(), MileageComparator);
  EXPECT_THAT(cars_, ::testing::ContainerEq(sorted_by_mileage_));
}

TEST_F(ComparatorTest, DynamicChangeComparatorPriceToYearToMileage) {
  sort(cars_.begin(), cars_.end(), PriceComparator);
  EXPECT_THAT(cars_, ::testing::ContainerEq(sorted_by_price_));
  sort(cars_.begin(), cars_.end(), YearComparator);
  EXPECT_THAT(cars_, ::testing::ContainerEq(sorted_by_year_));
  sort(cars_.begin(), cars_.end(), MileageComparator);
  EXPECT_THAT(cars_, ::testing::ContainerEq(sorted_by_mileage_));
}

} // end of unnamed namespace
} // end of comparator namespace
} // end of car namespace
