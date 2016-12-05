#include "player.h"
#include <memory>

class Drow:public Player, public std::enable_shared_from_this<Drow> {

public:
  Drow();  //constructor
  std::shared_ptr<Player> getBase() override;
};
