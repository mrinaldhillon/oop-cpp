#include "lib/intl.h"
#include <string>

Intl::Intl(float tution) {
  tution_ = tution;
  status_ = "International";
}

float Intl::GetTution() const { return tution_; }

const std::string& Intl::GetStatus() const { return status_; }
