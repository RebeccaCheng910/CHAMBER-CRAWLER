#ifndef _RH_H_
#define _RH_H_

#include "potion.h"

class RH: public Potion{
  static bool knownType;
public:
  RH(int row, int col);
  static bool isKnown();
  static void setKnown();
};
#endif
