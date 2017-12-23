#ifndef PIECHART_OBSERVER_H
#define PIECHART_OBSERVER_H

#include <iostream>
#include "lib/event.h"
#include "lib/observable.h"

namespace stock {

class PiechartObserver : public Observer {
 public:
  void update(const Observable& o, const Event& arg) {
    std::cout << "PieChart Observer:\t" << arg.getTicker() << "\t"
              << arg.getQuote() << "\n";
  }
};

}  // end of namespace stock

#endif  // PIECHART_OBSERVER_H
