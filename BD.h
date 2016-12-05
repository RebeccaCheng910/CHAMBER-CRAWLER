#ifndef _BD_H_
#define _BD_H_

#include "potion.h"
class BD: public Potion{
  static bool knownType;
public:
  BD(int row, int col);
  static bool isKnown();
  static void setKnown();
};
#endif

