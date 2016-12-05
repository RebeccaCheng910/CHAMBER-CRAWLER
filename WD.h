#ifndef _WD_H_
#define _WD_H_

#include "potion.h"

class WD: public Potion{
  static bool knownType;
public:
  WD(int row, int col);
  static bool isKnown();
  static void setKnown();
};
#endif

