#ifndef _WA_H_
#define _WA_H_

#include "potion.h"

class WA: public Potion{
  static bool knownType;
public:
  WA(int col, int row);
  static bool isKnown();
  static void setKnown();
};
#endif
