#ifndef REVERSE_ALPHABETICAL_COMPARATOR_H
#define REVERSE_ALPHABETICAL_COMPARATOR_H

#include <string>
#include "lib/comparator.h"

namespace fs {

class ReverseAlphabeticalComparator : public Comparator {
 public:
  bool operator()(const std::shared_ptr<FSElement>& e1,
                  const std::shared_ptr<FSElement>& e2) const {
    return e1->getName() > e2->getName();
  }
};

}  // end of namespace fs

#endif  // REVERSE_ALPHABETICAL_COMPARATOR_H
