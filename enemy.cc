#include "enemy.h"
#include "character.h"

Enemy::Enemy(int row, int col): Character{row, col,'e'} {
  HP = 140;  //human
  Atk = 20;
  Def = 20;
}

int Enemy::getHP() { return HP;}
int Enemy::getAtk() {return Atk;}
int Enemy::getDef() {return Def;}
