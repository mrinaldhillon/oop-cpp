#include "lib/outstate.h"
#include <string>

OutState::OutState(float tution) {
  tution_ = tution;
  status_ = "OutState";
}

float OutState::GetTution() const { return tution_; }

const std::string& OutState::GetStatus() const { return status_; }
