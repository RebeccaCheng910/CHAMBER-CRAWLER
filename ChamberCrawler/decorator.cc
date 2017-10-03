#include "decorator.h"
#include "player.h"
#include <memory>

using namespace std;

// constructor
Decorator::Decorator(shared_ptr<Player> p):Player{*p}, component{p} {}
