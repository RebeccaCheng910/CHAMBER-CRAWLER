#include "gold.h"
#include "object.h"
#include "info.h"
#include <string>

using namespace std;

//constructor, n take 0-8
Gold::Gold (int row, int col, int n): Object{row, col, 'G'} {
  if ( n >= 0 && n < 5) {  // normal pile
    value = 2;
    isProtected = false;
  } else if (n == 5) { // gragon hord
    value = 6;
    isProtected = true;
  } else if ( n == 6 || n == 7) { //small hoard
    value = 1;
    isProtected = false;
  } else if ( n == 10) {  //
     value = 4;
     isProtected = false;
  }
}

// destructor
Gold::~Gold() {}

// accessor
int Gold::getValue() {return value;}

bool Gold::getGold() {return isProtected;}


