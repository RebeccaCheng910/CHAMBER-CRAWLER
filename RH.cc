#include "potion.h"
#include "RH.h"

bool RH::knownType = false;

RH::RH(int row, int col): Potion{row, col, 0} {
  name = "RH";
}

bool RH::isKnown() {
  return knownType;
}

void RH::setKnown() {
  knownType = true;
}
