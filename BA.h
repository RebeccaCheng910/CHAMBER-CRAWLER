#ifndef _BA_H_
#define _BA_H_

#include "potion.h"

class BA: public Potion{
  static bool knownType;
public:
  BA(int row, int col);
  static bool isKnown();
  static void setKnown();
};
#endif
