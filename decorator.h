#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "player.h"

// abstract class
class Decorator: public player {
protected:
  Player *component;
public:
  Decorator(Player *p);  // constructor
};
