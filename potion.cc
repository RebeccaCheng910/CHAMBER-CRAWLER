#include "potion.h"
#include "object.h"
#include "info.h"
#include <string>

using namespace std;

//bool Potion::known = false;

// constructor
Potion::Potion (int row, int col, int t): Object(row, col, 'P'), type{t} {
}
// destructor
Potion::~Potion() {}


// accessor 
int Potion::getType() {return type;}
string Potion::getName() {return name;}
