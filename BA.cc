#include "BA.h"
#include "potion.h"

bool BA::knownType = false;

BA::BA(int row, int col):Potion(row,col,1){
  name = "BA";
}

bool BA::isKnown() {
  return knownType;
}

void BA::setKnown() {
  knownType = true;
}
