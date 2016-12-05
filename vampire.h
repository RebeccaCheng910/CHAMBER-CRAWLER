#include "player.h"
#include <memory>

class Vampire: public Player, public std::enable_shared_from_this<Vampire> {

public:
  Vampire(); 
  std::shared_ptr<Player> getBase() override;
};
