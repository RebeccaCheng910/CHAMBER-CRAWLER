#include "potion.h"
#include "PH.h"

bool PH::knownType = false;

PH::PH(int row, int col): Potion{row, col, 3} {
   name = "PH";
} 

bool PH::isKnown() {
  return knownType;
}

void PH::setKnown() {
  knownType = true;
}
