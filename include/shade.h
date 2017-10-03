#include "player.h"
#include <memory>
class Shade: public Player, public std::enable_shared_from_this<Shade> {

public:
  Shade();  // constructor
  std::shared_ptr<Player> getBase() override;
};
