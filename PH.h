#ifndef _PH_H_
#define _PH_H_

#include "potion.h"
class PH: public Potion {
  static bool knownType;
public:
  PH(int row, int col);
  static bool isKnown();
  static void setKnown();
};
#endif

