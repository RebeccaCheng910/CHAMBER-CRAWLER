#include "potion.h"
#include "object.h"
#include "info.h"
#include <string>

using namespace std;

// constructor

Potion::Potion (int row, int col, int t): Object(row, col, 'P'), type{t} {
	// set effect of Potion
	if (type == 0) {  // Restore Health (RH)
	  name = "RH";
	} else if (type == 1) {  // Boost Attack (BA) 
          name = "BA";
        } else if (type == 2) {  // Boost Defence (BD)
	  name = "BD";
	} else if (type == 3) {  // Poison Health (PH) 
	  name = "PH"; 
	} else if (type == 4) {  // Wound Attack (WA)
	  name = "WA";
	} else if (type == 5) {  // Wound Defence (WD)
	  name = "WD";
	}
}

// destructor
Potion::~Potion() {}


// accessor 
int Potion::getType() {return type;}
string Potion::getName() {return name;}
