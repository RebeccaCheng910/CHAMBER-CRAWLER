#include "enemy.h"
#include "dragon.h"
#include <string>

using namespace std;

Dragon::Dragon(int row, int col, char type): Enemy{row, col,type} {
	HP = 150;
	Atk = 20;
	Def = 20;  
}

Dragon::~Dragon() {}

  
