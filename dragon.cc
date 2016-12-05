#include "enemy.h"
#include "dragon.h"
#include <string>
#include <memory>

using namespace std;

Dragon::Dragon(int row, int col, char type): Enemy{row, col,type} {
	HP = 150;
	Atk = 20;
	Def = 20;  
}

Dragon::~Dragon() {}

void Dragon::setHoard (const shared_ptr<Gold> &hoard) {
	g = hoard;
}

shared_ptr<Gold> Dragon::getHoard() {return g;}
