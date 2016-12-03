#include "decorator.h"
#include "player.h"

// constructor
Decorator::Decorator(Player *p):Player{}, component{p} {}
