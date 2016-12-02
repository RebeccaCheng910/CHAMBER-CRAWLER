#include "potion.h"
#include "object.h"
#include "info.h"
#include <string>

using namespace std;

// constructor

Potion::Potion (int row, int col, char c, int t): Object(row, col,c) {
	type = t;
	// set effect of Potion
	if (type == 0) {  // Restore Health (RH)
		effectHP = 10;
	} else if (type == 1) {  // Boost Attack (BA) 
    effectAtk = 5;
  } else if (type == 2) {  // Boost Defence (BD)
		effectDef = 5;
	} else if (type == 3) {  // Poison Health (PH) 
		effectHP = -10; 
	} else if (type == 4) {  // Wound Attack (WA)
		effectAtk = -5;
	} else if (type == 5) {  // Wound Defence (WD)
		effectDef = -5; 
	}
}

// destructor
Potion::~Potion() {}


// accessor 
int Potion::getType() {return type;}
int Potion::getEffectHP() {return effectHP;}
int Potion::getEffectAtk() {return effectAtk;}
int Potion::getEffectDef() {return effectDef;}

		
