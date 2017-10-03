#include "character.h"
#include "object.h"
#include <iostream>
#include <string>

using namespace std;

// constructor
Character::Character(int row, int col, char type): Object{row, col, type} {
}

string Character::getRace() { return race;}

int Character::getHP(){
  return HP;
}


int Character::getAtk(){
  return Atk;
}

int Character::getDef(){
  return Def;
}

// destructor
Character::~Character() {}
