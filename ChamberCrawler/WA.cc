#include "potion.h"
#include "WA.h"

bool WA::knownType = false;

WA::WA(int row, int col): Potion{row, col, 4} {
  name = "WA";
} 

bool WA::isKnown() {
  return knownType;
}

void WA::setKnown() {
  knownType = true;
}
