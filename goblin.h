#ifndef _GOBLIN_H_
#define _GOBLIN_H_

#include "player.h"
#include <memory>

class Goblin:public Player, public std::enable_shared_from_this<Goblin> {


public:
  Goblin();
  std::shared_ptr<Player> getBase() override;
};
#endif
