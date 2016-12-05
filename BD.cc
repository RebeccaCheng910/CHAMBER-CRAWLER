#include "potion.h"
#include "BD.h"

bool BD::knownType = false;

BD::BD(int row, int col):Potion{row, col, 2} {
  name = "BD";
};

bool BD::isKnown() {
  return knownType;
}

void BD::setKnown() {
  knownType = true;
}
