#ifndef CAR_H
#define CAR_H

namespace car {

class Car {
 private:
  int price_;
  int year_;
  float mileage_;

 public:
  Car(int price, int year, float mileage)
      : price_(price), year_(year), mileage_(mileage) {}

  int price() const;
  int year() const;
  float mileage() const;

  bool operator==(const Car& rhs) const;
};

}  // end of namespace car

#endif  // CAR_H
