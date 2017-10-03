#include "player.h"
#include <memory>

class Troll: public Player, public std::enable_shared_from_this<Troll> {

public:
  Troll(); 
  std::shared_ptr<Player> getBase() override;
};

