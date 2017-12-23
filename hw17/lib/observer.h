#ifndef OBSERVER_H
#define OBSERVER_H

namespace stock {

class Observable;
class Event;

class Observer {
 public:
  virtual void update(const Observable& o, const Event& arg) = 0;
  virtual ~Observer() = default;
};

}  // end of namespace stock
#endif  // OBSERVER_H
