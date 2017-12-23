#ifndef STOCK_QUOTE_OBSERVABLE_H
#define STOCK_QUOTE_OBSERVABLE_H

#include <map>
#include <string>
#include "lib/observable.h"
#include "lib/stock_event.h"

namespace stock {

class StockQuoteObservable : public Observable {
 private:
  std::map<std::string, float> map_{};

 public:
  void changeQuote(const std::string& ticker, float quote) {
    map_[ticker] = quote;
    setChanged();
    notifyObservers(StockEvent(ticker, quote));
  }
};

}  // end of namespace stock
#endif  // STOCK_QUOTE_OBSERVABLE_H
