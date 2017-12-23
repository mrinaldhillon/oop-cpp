#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <memory>
#include <vector>
#include "lib/event.h"
#include "lib/observer.h"

namespace stock {

class Observable {
 private:
  bool changed_ = false;
  std::vector<std::weak_ptr<Observer>> observers_{};

 public:
  void addObserver(const std::shared_ptr<Observer>& o) { observers_.push_back(o); }
  void setChanged() { changed_ = true; }
  bool hasChanged() const { return changed_; }
  void clearChanged() { changed_ = false; }
  void notifyObservers() {
    // TBD
  }

  void notifyObservers(const Event& arg) {
    if (!hasChanged()) return;

    for (const auto weak_o : observers_) {
      if (auto o = weak_o.lock()) {
        o->update(*this, arg);
      }
    }
    clearChanged();
  }
};

}  // end of namespace stock

#endif  // OBSERVABLE_H
