#ifndef THREE_D_OBSERVER_H
#define THREE_D_OBSERVER_H

#include <iostream>
#include "lib/event.h"
#include "lib/observable.h"

namespace stock {

class ThreeDObserver : public Observer {
 public:
  void update(const Observable& o, const Event& arg) {
    std::cout << "3D Observer:\t" << arg.getTicker() << "\t"
              << arg.getQuote() << "\n";
  }
};

}  // end of namespace stock

#endif  // THREE_D_OBSERVER_H
