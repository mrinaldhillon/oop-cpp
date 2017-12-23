#include <stdlib.h>
#include <map>
#include <memory>
#include <string>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libstock_observer.h"

namespace stock {

namespace {

std::string getStdout(StockQuoteObservable& o, const std::string& company,
                      int random) {
  std::stringstream buffer;
  std::streambuf* sbuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());
  o.changeQuote(company, random);
  std::string output = buffer.str();
  std::cout.rdbuf(sbuf);
  return output;
}

TEST(ObserverTest, observerNotify) {
  StockQuoteObservable observable;
  auto pc_observer = std::make_shared<PiechartObserver>();
  auto table_observer = std::make_shared<TableObserver>();
  auto three_d_observer = std::make_shared<ThreeDObserver>();
  observable.addObserver(pc_observer);
  observable.addObserver(table_observer);
  observable.addObserver(three_d_observer);
  for (int i = 0; i < 3; i++) {
    int random = rand() % 100;

    std::string output = getStdout(observable, "company1", random);

    std::ostringstream oss;
    oss << "PieChart Observer:\tcompany1\t" << random << "\n"
        << "Table Observer:\tcompany1\t" << random << "\n"
        << "3D Observer:\tcompany1\t" << random << "\n";

    EXPECT_EQ(output, oss.str());
    std::cout << oss.str();
    sleep(2);
  }
}

}  // end of unnamed namespace
}  // end of namespace stock
