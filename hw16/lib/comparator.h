#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "fs_element.h"

namespace fs {

class Comparator {
 public:
  virtual bool operator()(const std::shared_ptr<FSElement>& e1,
                          const std::shared_ptr<FSElement>& e2) const = 0;
  virtual ~Comparator() = default;
};

}  // end of namespace fs

#endif  // COMPARATOR_H
