#include "merchant.h"
#include <string>
 
using namespace std;
 
Merchant::Merchant(int row, int col, char type): Enemy{row, col,type} {
  HP = 30;
  Atk = 70;
  Def = 5;
}

bool Merchant::isHostile = false;

Merchant::~Merchant() {}

bool Merchant::getHostility() {return isHostile;}

void Merchant::setHostility(bool status) {isHostile = status;}

