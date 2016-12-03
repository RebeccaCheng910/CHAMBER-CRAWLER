#include "character.h"
#include "object.h"
#include <iostream>
#include <string>

using namespace std;

// constructor
Character::Character(int row, int col, char type): Object{row, col, type} {
}

string Character::getRace() { return race;}
