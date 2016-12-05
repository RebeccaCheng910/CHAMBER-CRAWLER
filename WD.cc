#include "potion.h"
#include "WD.h"

bool WD::knownType = false;

WD::WD(int row, int col): Potion{row, col, 5} {
  name = "WD";
 } 

bool WD::isKnown() {
  return knownType;
}

void WD::setKnown() {
  knownType = true;
}
