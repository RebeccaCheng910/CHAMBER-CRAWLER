#include "gold.h"
#include "object.h"
#include "info.h"
#include <string>

using namespace std;

//constructor
Gold::Gold (int row, int col, int n, bool isProtected): Object{row, col, 'G'} {
	value = n;
	isProtected = isProtected;
}

// destructor
Gold::~Gold() {}

// accessor
int Gold::getValue() {return value;}

bool Gold::getGold() {return isProtected;}


