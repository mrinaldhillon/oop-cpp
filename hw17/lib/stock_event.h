#ifndef STOCK_EVENT_H
#define STOCK_EVENT_H

#include <string>
#include "lib/event.h"

namespace stock {

class StockEvent : public Event {
 private:
  std::string ticker_;
  float quote_;

 public:
  StockEvent(const std::string ticker, float quote)
      : ticker_(ticker), quote_(quote) {}

  float getQuote() const { return quote_; }
  void setQuote(float quote) { quote_ = quote; }
  std::string getTicker() const { return ticker_; }
  void setTicker(const std::string& ticker) { ticker_ = ticker; }
};

}  // end of namespace stock

#endif  // STOCK_EVENT_H
