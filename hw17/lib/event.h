#ifndef EVENT_H
#define EVENT_H

#include <string>

namespace stock {

class Event {
 public:
  virtual ~Event() = default;
  virtual float getQuote() const = 0;
  virtual void setQuote(float quote) = 0;
  virtual std::string getTicker() const = 0;
  virtual void setTicker(const std::string& ticker) = 0;
};

}  // end of namespace stock

#endif  // EVENT_H
