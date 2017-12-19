#ifndef TIMESTAMP_COMPARATOR_H
#define TIMESTAMP_COMPARATOR_H

#include <string>
#include "lib/comparator.h"

namespace fs {

class TimestampComparator : public Comparator {
 public:
  bool operator()(const std::shared_ptr<FSElement>& e1,
                  const std::shared_ptr<FSElement>& e2) const {
    return e1->getModTime() < e2->getModTime();
  }
};

}  // end of namespace fs

#endif  // TIMESTAMP_COMPARATOR_H
