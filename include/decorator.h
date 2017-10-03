#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include <memory>
#include "player.h"

// abstract class
class Decorator: public Player {
protected:
  std::shared_ptr<Player> component;
public:
  Decorator(std::shared_ptr<Player>);  // constructor
};

#endif
