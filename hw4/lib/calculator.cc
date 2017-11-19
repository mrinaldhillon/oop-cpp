#include "calculator.h"
#include <stdexcept>

using namespace std;

float Calculator::multiply(float x, float y) { return x * y; }

float Calculator::divide(float x, float y) {
  if (0 == y) throw invalid_argument("division by zero");
  return x / y;
}
