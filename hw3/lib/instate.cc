#include "lib/instate.h"
#include <string>

InState::InState(float tution) {
  tution_ = tution;
  status_ = "InState";
}

float InState::GetTution() const { return tution_; }

const std::string& InState::GetStatus() const { return status_; }
