#ifndef TABLE_OBSERVER_H
#define TABLE_OBSERVER_H

#include <iostream>
#include "lib/event.h"
#include "lib/observable.h"

namespace stock {

class TableObserver : public Observer {
 public:
  void update(const Observable& o, const Event& arg) {
    std::cout << "Table Observer:\t" << arg.getTicker() << "\t"
              << arg.getQuote() << "\n";
  }
};

}  // end of namespace stock

#endif  // TABLE_OBSERVER_H
